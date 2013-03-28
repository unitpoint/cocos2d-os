
ColorNode = extends Node {
	__object = {
		color: [0.5, 0.7, 0.5, 1],
	},
	
	paint = function(){
		@drawBB(@color, true)
	},
}
