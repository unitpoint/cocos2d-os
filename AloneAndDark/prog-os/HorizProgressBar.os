// require("image")

HorizProgressBar = extends Image {
	__object = {
		__percentage = 0,
		__progressImage = null,
	},

	__construct = function(outer, inner){
		super(outer)
		@__progressImage = Image(inner).attrs {
			anchor = [0, 0],
			x = 0,
			y = 0,
			width = 0,
			frameWidth = 0,
		}.insertTo(this)
	},
	
	__get@percentage = function(){ @__percentage },
	__set@percentage = function(a){
		var width = (@__percentage = math.clamp(a, 0, 100)) / 100 * @width
		@__progressImage.attrs {
			width = width,
			frameWidth = width,
		}
	},
}
