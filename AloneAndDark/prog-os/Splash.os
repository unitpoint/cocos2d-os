Splash = extends Scene {
	__construct = function(){
		super()
		
		// setTimeout(function(){ director.scene = require("game")() });
		
		var fill = ColorNode().insertTo(this).attrs {
			color = [0, 0, 0],
			x = @width/2,
			y = @height/2,
		}
		
		var group = Group().insertTo(this)
		
		Image("splash-company-512").insertTo(group).attrs{
			opacity = 0,
			x = @width/2,
			y = @height/2,
		}.transition{
			opacity = 1,
			duration = 2,
			easy = Easy.outQuad,
		}
		
		var progressBar = HorizProgressBar("progressbar-border", "progressbar").insertTo(group).attrs{
			anchor = [0.5, 1],
			x = @width/2,
			y = @height*0.95,
		}
		var function updateProgressBar(){
			progressBar.percentage = progressBar.percentage + 60
			if(progressBar.percentage >= 100){
				@clearTimeout(updateProgressBar)
				@transition {
					delay = 0.5,
					duration = 1,
					opacity = 0,
					easy = Easy.outCubic,
					onComplete = function(){
						director.scene = Game()
					},
				}
			}
		}
		group.setTimeout(updateProgressBar, 0.1, true)
		// @addEventHandler("enterFrame", function(){})
	}
}