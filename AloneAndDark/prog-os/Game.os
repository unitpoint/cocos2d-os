
var function fillRect(image, offsX, offsY, areaWidth, areaHeight, paintParams){
	var width, height = image.width, image.height
	offsX, offsY = offsX % width, offsY % height
	if(offsX < 0) offsX = offsX + width
	if(offsY < 0) offsY = offsY + height
	image.width, image.height = width + 0.5, height + 0.5
	for(var y = -offsY; y < areaHeight; y = y + height){
		image.y = y;
		for(var x = -offsX; x < areaWidth; x = x + width){
			image.x = x;
			image.handlePaint(paintParams)
		}
	}
	image.width, image.height = width, height
}

var levelMap = {
	sky = "sky",
	layers = {
		houses = {
			y = 0.8,
			items = [
				{
					class = "House",
					image = "house-01",
					x = 0,
					windows = [
						{
							image = "house-01-w1",
							x = 181,
							y = 201,
						},
					],
				},
				{
					class = "House",
					image = "house-01",
					x = 900,
				},
			],
		},
	},
}

LayerImage = extends Image {
	__construct = function(game, params){
		super(params.image)
		delete params.image
		@attrs params
	}
}

House = extends LayerImage {
	__construct = function(game, params){
		super(game, params)
	}
}

var animations = {}

function(){
	var config = eval('return '..File.readContents("zombie-01.json"))
	var monsterAnims = {
		walkRight = [61, 81],
	}
	var animations = animations['zombie-01'] = {}
	for(var name, p in monsterAnims){
		var anim = animations[name] = { delay = 0.09, frames = [] }
		for(var i = p[0]; i <= p[1]; i++){
			var cf = config.frames["Image ${i}.png"]
			if(cf)
				anim.frames[] = {
					left = cf.frame.x,
					top = cf.frame.y,
					width = cf.frame.w,
					height = cf.frame.h,
				}
		}
	}
	// print animations
	// print config
}()

Monster = extends Sprite {
	__object = {
		curAnimName = "",
		curAnim = null,
	},
	
	__construct = function(filename){
		super(filename)
		@animations = animations[filename]
		@runAnimation("walkRight")
	},
	
	runAnimation = function(name, onComplete){
		@curAnimName == name && !onComplete && return;
		@curAnimName = name
		@stopAnimation(@curAnim)
		@curAnim = @animation(@animations[name], onComplete)
	},
}

Sky = extends Group {
	__construct = function(game, filename){
		super()
		@game = game
		@image = Image(filename).attrs {
			anchor = [0, 0],
		}
		// @anchor = [0, 0]
	},
	
	paint = function(params){
		fillRect(@image, @game.levelScrollX * -0.1, 0, @width, @image.height, params)
	},
}

var randomGenSeed = 0
var function randomGen(){
	randomGenSeed = randomGenSeed ^ (randomGenSeed<<6) + (randomGenSeed>>2) + 0b1010101010
	return (randomGenSeed & 0xffff) / 0xffff
}

var LAYER = 'SKY MOON MAP WINDOWS MONSTERS LIGHT_AREA'.split(' ').flip()

Game = extends Scene {
	__construct = function(){
		super()
		
		var layers = @layers = {}
		
		@sky = Sky(this, levelMap.sky).insertTo(this).attrs { zOrder = LAYER.SKY }
		
		@moon = Image("moon").insertTo(this).attrs {
			x = 100,
			y = 70,
			zOrder = LAYER.MOON,
		}
		
		@houseWindowsLayer = Group().insertTo(this).attrs {
			anchor = [0, 0],
			height = @height,
			x = 0,
			y = 0, // (layer.y || 1) * height,
			paralaxScale = levelMap.layers.houses.paralaxScale || 1,
			zOrder = LAYER.WINDOWS,
		}
		for(var name, layer in levelMap.layers){
			var layerGroup = layers[name] = Group().insertTo(this).attrs {
				anchor = [0, 0],
				height = @height,
				x = 0,
				y = 0, // (layer.y || 1) * height,
				paralaxScale = layer.paralaxScale || 1,
				zOrder = LAYER.MAP,
			}
			for(var _, item in layer.items){
				var classname = item.class; delete item.class
				item.y = (item.y || layer.y || 1) * @height
				item.anchor = item.anchor || [0.5, 1]
				_E[classname](this, item).insertTo(layerGroup)
			}
		}
		
		@monster = Monster("zombie-01").insertTo(this).attrs {
			anchor = [0.5, 1],
			x = @width / 2,
			y = @height * 0.9,
			zOrder = LAYER.MONSTERS,
		}
		
		@lightarea = Image("lightarea-02").insertTo(this).attrs {
			x = @monster.x,
			y = @height * 0.6, // @monster.y + @monster.height * (0.5 - @monster.anchor.y),
			scale = 1.5 * 4,
			zOrder = LAYER.LIGHT_AREA,
		}
		
		var x = 0
		@addEventListener('enterFrame', function(params){
			@levelScrollX = x = x - @width * params.deltaTime / 15
			// print "levelScrollX: ${x}"
		})
		
		addStats(this)
	},
	
	__get@levelScrollX = function(){ @__levelScrollX },
	__set@levelScrollX = function(x){
		@__levelScrollX = x
		for(var _, layer in @layers){
			layer.x = x * layer.paralaxScale
		}
	},
	
	paint = function(params){
		
	},
}