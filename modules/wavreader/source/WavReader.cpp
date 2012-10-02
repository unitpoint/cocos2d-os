#include "WavReader.h"
#include "IwFile.h"
#include "IwRuntime.h"
#include "IwDebug.h"
#include "string.h"

WavReader::SoundData::SoundData()
{
	format = PCM_16BIT_MONO;
	pitch = 44100;		
	samples = NULL;
	sample_count = 0;
	buffer_size = 0;
}

WavReader::SoundData::SoundData(ESoundDataFormat p_format, int p_pitch)
{
	format = p_format;
	pitch = p_pitch;		
	samples = NULL;
	sample_count = 0;
	buffer_size = 0;
}

WavReader::SoundData::~SoundData()
{
	delete [] samples;
}

// void setSampleCount(uint32);
void WavReader::SoundData::setBufferSize(int size)
{
    // Do nothing if not changing
    if (size == buffer_size && samples)
        return;

    if (samples)
        delete [] samples;

    // Create the buffer
    sample_count = size;

    switch (format)
    {
    case ADPCM_MONO:
        sample_count = size*2;
        break;

    case PCM_8BIT_MONO:
        sample_count = size;
        break;
    default:                // Default to 16-bit
    case PCM_16BIT_MONO:
        sample_count = size/2;
        break;
    };

    buffer_size = size;
    samples = new int8[buffer_size];
}
		
void WavReader::SoundData::switchDataSign()
{
	for(int i = 0; i < buffer_size; i++){
		samples[i] += (int8) 0x80;
	}
}

WavReader::WavReader()
{
}

WavReader::SoundData * WavReader::load(const char * filename)
{
	return WavReader().loadInternal(filename);
}

WavReader::SoundData * WavReader::loadInternal(const char * filename)
{
    IW_CALLSTACK("WavReader::load");

	this->filename = filename;

    SoundData * data = NULL; // Object to return

    // Open file
    s3eFile* pFile = IwFileOpenPrefixed(filename, "rb");
    IwAssertMsg(SOUND, pFile, ("Could not load file %s", filename));
    if (!pFile)
        return NULL;

    // Read RIFF header - Gives the file size and checks that this is a WAVE
    // file as expected
    RIFFHeader riffHeader;
    if ((s3eFileRead(&riffHeader, sizeof(RIFFHeader), 1, pFile) != 1)
        || (strncmp(riffHeader.typeID, "RIFF", 4) != 0)
        || (strncmp(riffHeader.subTypeID, "WAVE", 4) != 0))
    {
        IwAssertMsg(SOUND, false, ("Invalid header in %s (RIFF Header)", filename));
        s3eFileClose(pFile);
        return NULL;
    }

    // Read in RIFF chunks until we reach the end of the file
    // Read the RIFF chunk header. This tells us what type of chunk follows.
    RIFFChunkHeader chunkHeader;
    bool readData = false;
    uint32 fileSize = s3eFileGetSize(pFile);

    while (readChunkHeader(chunkHeader, *(s3eFile*)pFile))
    {
        uint32 chunkStartPos = s3eFileTell(pFile);

        // Next action depends on chunk type. The order of this is important and we may fail
        // if an unexpected chunk type is found
        if (!strncmp(chunkHeader.typeID, "fmt ", 4))
        {
            // Read WAVE info chunk
            if (!readChunkFormat(chunkHeader, data, *(s3eFile*)pFile))
            {
                s3eFileClose(pFile);
                return NULL;
            }
        }
        else if (!strncmp(chunkHeader.typeID, "data", 4))
        {
            if (!readChunkData(chunkHeader, data, *(s3eFile*)pFile))
            {
                s3eFileClose(pFile);
                return NULL;
            }
            readData = true;
        }
        else if (!strncmp(chunkHeader.typeID, "fact", 4))
        {
            if (!readChunkFact(chunkHeader, data, *(s3eFile*)pFile))
            {
                s3eFileClose(pFile);
                return NULL;
            }
        }
        else
        {
            // Unknown chunk type
            // Make a proper string from the chunk type info
            char typeID[5];
            strncpy(typeID, chunkHeader.typeID, 4);
            typeID[4] = 0;  // Terminate

            const char* g_IgnoreTypes = "LIST" //LIST is just copyright info etc.
                "DISP";  //DISP seems to be info about what package exported it

            IwAssertMsg(SOUND, strstr(g_IgnoreTypes, typeID), ("Unhandled chunk type '%s' in %s. Ignoring this data.", typeID, filename));
        }

        // Exit if at end of file
        if (chunkStartPos + chunkHeader.length >= fileSize)
            break;

        // Move to next chunk
        s3eFileSeek(pFile, chunkStartPos + chunkHeader.length, S3E_FILESEEK_SET);
    }

    // Check that we have read the sample data
    IwAssertMsg(SOUND, readData, ("No data chunk read in %s", filename));
    s3eFileClose(pFile);
    return data;
}
//-------------------------------------------------------------------------
bool WavReader::readChunkHeader(RIFFChunkHeader& header, s3eFile& file)
{
    return (s3eFileRead(&header, sizeof(RIFFChunkHeader), 1, &file) == 1);
}
//-------------------------------------------------------------------------
bool WavReader::readChunkFormat(const RIFFChunkHeader& header, SoundData*& data, s3eFile& file)
{
    WAVEFormatChunkADPCM format;

    // Read data from file
    if ((header.length < sizeof(WAVEFormatChunk))
        || (s3eFileRead(&format, sizeof(WAVEFormatChunkADPCM), 1, &file) != 1))
    {
        IwAssertMsg(SOUND, false, ("Invalid format chunk in WAV file"));
        return false;
    }

    IwAssertMsg(SOUND, format.channels == 1, ("%s has more than 1 channel. IwSound is mono only", filename));

    // Create object based on header info
    switch (format.formatTag)
    {
    default:    // Unsupported format - Exit without creating data
        IwAssertMsg(SOUND, false, ("Unsupported WAVE file format (%d)", format.formatTag));
        return false;
        break;

    case WAVE_FORMAT_PCM:   // Raw PCM data. Bits per sample can be 8 or 16
        // Bits per sample will have been read into pad bytes of format info
        switch (format.bitsPerSample)
        {
        case 8:     // 8 bps
            data = new SoundData(PCM_8BIT_MONO, format.samplesPerSec);
            break;

        case 16:    // 16 bps
            data = new SoundData(PCM_16BIT_MONO, format.samplesPerSec);
            break;

        default:    // Unhandled
            IwAssertMsg(SOUND, false, ("Unsupported bits-per-sample (%d)", format.bitsPerSample));
            return false;
            break;
        }
        break;

    case 17:
            // ADPCM compressed data
			IwAssertMsg(SOUND, false, ("Unsupported format (ADPCM compressed data)"));
            break;
    }

    return true;
}
//-------------------------------------------------------------------------
bool WavReader::readChunkData(const RIFFChunkHeader& header, SoundData*& data, s3eFile& file)
{
    // Check that we have already read a format chunk and the object has been created
    if (!data)
    {
        IwAssertMsg(SOUND, false, ("Data chunk encountered before format chunk in %s", filename));
        return false;
    }

    // If the number of samples has already been set then check we're not changing it
#ifdef IW_USE_ASSERTIONS
    uint32 currentBufSiz = data->buffer_size;


    IwAssertMsg(SOUND, (currentBufSiz ==  0) || (header.length == currentBufSiz),
                        ("Unexpected data size in %s", filename));
#endif

    // Create the data array
    data->setBufferSize((int)header.length);

    // Read in the actual data. This can be read straight into the array independent of BPS
    if (s3eFileRead(&data->samples[0], 1, header.length, &file) != header.length)
    {
        IwAssertMsg(SOUND, false, ("Error reading WAVE file data from %s", filename));
        return false;
    }

    // DJB - Our 8-bit samples seem to be saved as unsigned data. Don't why this is or a way
    // to distinguish signed from unsigned.
    // Transform all 8-bit samples for now
    // DP - wav files are 8-bit unsigned and 16-bit signed, thats just the (random) way they are
    if (data->format == PCM_8BIT_MONO)
        data->switchDataSign();

    return true;
}
//-------------------------------------------------------------------------
bool WavReader::readChunkFact(const RIFFChunkHeader& header, SoundData*& data, s3eFile& file)
{
    uint32 sampleCount;
    if (s3eFileRead(&sampleCount, sizeof(uint32), 1, &file) != 1)
    {
        IwAssertMsg(SOUND, false, ("Error reading WAVE file info from %s", filename));
        return false;
    }

	data->sample_count = sampleCount;
    return true;
}
