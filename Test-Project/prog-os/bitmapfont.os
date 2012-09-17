_E = extends _E {}
_G.BitmapFont = _E

function parseConfig(filename){
	var tokens = LangTokenizer.parseFile(filename)
	// print tokens
	var error, token
	var next_index = 0
	var function readToken(){ return error ? null : tokens[next_index++] }
	var function expectStr(str){
		var token = readToken()
		if(token.str != str){
			print "expect str ERR "..str.." token "..token.." error "..error.." next index "..next_index.." tokens "..#tokens
			error = "expect str: "..str
			return
		}
		return token
	}
	var function isNextType(){
		var save_error = error
		var save_index = next_index
		for(var i, arg in arguments){
			var token = readToken()
			// print "is next type "..arg.." "..token
			if(token.type != arg){
				// print "is next type ERR"
				error = save_error
				next_index = save_index
				return false
			}
		}
		// print "is next type OK"
		error = save_error
		next_index = save_index
		return true
	}
	var function readValues(){
		var values = []
		for(;;){
			var token = readToken()
			if(!token) return;
			values.push(token.str)
			if(!isNextType(LangTokenizer.TOKEN_TYPE_OPERATOR)) return #values > 1 ? values : values[0];
			if(!expectStr(",")) return;
		}
	}
	var function readProperies(){
		var props = {}
		for(; isNextType(LangTokenizer.TOKEN_TYPE_NAME, LangTokenizer.TOKEN_TYPE_OPERATOR); ){
			var name = readToken()
			if(!expectStr("=")) return;
			var values = readValues()
			// print "values "..values
			if(!values) return;
			props[name.str] = values
			// print props
		}
		// print props; terminate()
		return props;
	}
	var function readChars(){
		if(!expectStr("count") || !expectStr("=")) return;
		var count = readToken()
		if(!count) return;
		count = numberof count.str
		var chars = {}
		for(var i = 0; i < count; ++i){
			if(!expectStr("char")) return;
			var props = readProperies()
			if(!props) return;
			chars[props.id] = props
		}
		return chars
	}
	var function readKernings(){
		if(!expectStr("count") || !expectStr("=")) return;
		var count = readToken()
		if(!count) return;
		count = numberof count.str
		var kernings = []
		for(var i = 0; i < count; ++i){
			if(!expectStr("kerning")) return;
			var props = readProperies()
			if(!props) return;
			kernings[] = props
		}
		return kernings
	}
	
	var config = {}
	for(;;){
		token = readToken()
		if(token.str == "info" || token.str == "common" || token.str == "page"){
			config[token.str] = readProperies()
			if(!config[token.str]) return;
			continue
		}
		if(token.str == "chars"){
			var chars = readChars();
			if(!chars) return;
			config.chars = chars
			continue
		}
		if(token.str == "kernings"){
			var kernings = readKernings();
			if(!kernings) return;
			config.kernings = kernings
			continue
		}
		print "cur token "..token.." next index "..next_index; print "config "..config; terminate()		
	}
	return config
}

// print(parseConfig("arial-en-ru-32.fnt"))


