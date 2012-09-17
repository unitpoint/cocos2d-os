Hi guys, I'm working on new embedded language ObjectScript that mixes benefits of JavaScript, Lua and PHP. The ObjectScript looks like JavaScript but very light and much improved (OOP, multiple assignment, simple syntax, native JSON support, properties, getters and setters, iterators, multi dimensional properties and so on). 

You could read brief article "Programming in ObjectScript" here 
https://github.com/unitpoint/objectscript/wiki/Programming-in-ObjectScript

At the moment I'd like to introduce you the first step of new engine made with ObjectScript and Marmalade SDK, just download it here
https://github.com/unitpoint/cocos2d-os/zipball/stable-1

unzip downloaded archive and run GameExample\GameExample.mkb, compile it using your MVC and play with it. GameExample is not real game at the moment, it looks like test of ObjectScript or demo. The demo contains color rects that are moving. You have ability to touch one of the rects and drag it. The rect goes to front plan when you touch it and go to original place when you release it.

Major script files:

GameExample\assets\main.os - main program, it creates MyScene and inserts some number of MyColorRect nodes to the scene.
GameExample\assets\director.os - engine director, it triggers events
GameExample\assets\node.os - base node class, it looks like a layer
GameExample\assets\core.os - ObjectScript core functions

Output files:

GameExample\assets-ram\output.txt - output console

GameExample\assets-ram\main.txt - compiled text file of main.os, so you could view how the ObjectScript runs (for debug purposes)
GameExample\assets-ram\main.osc - compiled binary file
GameExample\assets-ram\main.osd - compiled debug info file (for debug purposes)

... and so on for each ObjectScript source code file

A: What now?
Q: I'm going to do:
- write real demo game with ObjectScript and Marmalade SDK
- finalize specification of ObjectScript
- finalize core, virtual machine (VM) and garbage collector (GC) of ObjectScript
- write more documentations and examples

A: Why ObjectScript?
Q: I create applications and games more than 20 years and I'm ready now to create light and powerful universal language with no compromises.

A: Could ObjectScript be integrated with C++? 
Q: Absolutely, it's designed to be integrated with C++

A: Why Marmalade SDK?
Q: Marmalade SDK is very powerful but it's low level SDK. I'm going to create powerful and simple high level of Marmalade SDK, like Corona SDK but with ObjectScript, it'll give ability to create games easily and quickly, the Marmalade SDK will be much more known in the world.

ObjectScript code exampple:

<code>var autoTouchId = 0
function registerTouchEvent(x y phase id){
	if(id == 0){
		id = phase == "start" ? --autoTouchId : autoTouchId
	}
	if(phase == "start"){
		touches[id] = {
			x = x
			y = y
			phase = phase
			processed = false
			id = id
			captured = null
		}
		return
	}
	if(!(id in touches)){
		return
	}
	var touch = touches[id]
	if(phase == "move"){
		if(touch.phase == "start"){
			if(!touch.processed){
				touch.x = x
				touch.y = y
				return
			}
		}else if(touch.phase != "move"){
			return
		}
	}
	touch.x = x
	touch.y = y
	touch.phase = phase
	touch.processed = false
	touch.id = id
}</code>

To be continued...
