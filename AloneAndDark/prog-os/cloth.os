/*
Copyright (c) 2013 Stuffit at codepen.io (http://codepen.io/stuffit)

View this and others at http://lonely-pixel.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

// settings

var physics_accuracy = 5
var mouse_influence      = 20
var mouse_cut            = 6
var gravity              = 900
var cloth_height         = 30
var cloth_width          = 50
var start_y              = 20
var spacing              = 7
var tear_distance        = 60

var canvas,
	ctx,
	cloth,
	boundsx,
	boundsy
	
var mouse = {
		down: false,
		button: 1,
		x: 0,
		y: 0,
		px: 0,
		py: 0
	};

	canvas = document.getElementById('c');
	ctx    = canvas.getContext('2d');

	canvas.width  = 600;//window.innerWidth;
	canvas.height = 320;//window.innerHeight;

	canvas.onmousedown = function(e) {
		mouse.button = e.which;
		mouse.px = mouse.x;
		mouse.py = mouse.y;
		mouse.x = e.clientX || e.lvyerX;
		mouse.y = e.clientY || e.lvyerY;
		mouse.down = true;
		e.preventDefault();
	};

	canvas.onmouseup = function(e) {
		mouse.down = false;
		e.preventDefault();
	};

	canvas.onmousemove = function(e) {
		mouse.px = mouse.x;
		mouse.py = mouse.y;
		mouse.x = e.clientX || e.lvyerX;
		mouse.y = e.clientY || e.lvyerY;
		e.preventDefault();
	};

	canvas.oncontextmenu = function(e) {
		e.preventDefault(); 
	};

	boundsx = canvas.width - 1;
	boundsy = canvas.height - 1;

	ctx.strokeStyle = 'rgba(222,222,222,0.6)';
	cloth = new Cloth();
	update();


var Point = {
	__construct = function(x, y) {
		@x = x;
		@y = y;
		@px = x;
		@py = y;
		@vx = 0;
		@vy = 0;
		@pin_x = null;
		@pin_y = null;
		@constraints = [];
	},

	update = function(delta) {
		if (mouse.down) {
			var diff_x = @x - mouse.x,
				diff_y = @y - mouse.y,
				dist   = Math.sqrt(diff_x * diff_x + diff_y * diff_y);

			if (mouse.button == 1) {

				if(dist < mouse_influence) {
					@px = @x - (mouse.x - mouse.px) * 1.8;
					@py = @y - (mouse.y - mouse.py) * 1.8;
				}

			} else if (dist < mouse_cut) @constraints = [];
		}

		@add_force(0, gravity);

		delta *= delta;
		nx = @x + ((@x - @px) * .99) + ((@vx / 2) * delta);
		ny = @y + ((@y - @py) * .99) + ((@vy / 2) * delta);

		@px = @x;
		@py = @y;

		@x = nx;
		@y = ny;

		@vy = @vx = 0
	},

	draw = function() {
		if (@constraints.length <= 0) return;
		
		var i = @constraints.length;
		while(i--) @constraints[i].draw();
	},

	resolve_constraints = function() {
		if (@pin_x != null && @pin_y != null) {
			@x = @pin_x;
			@y = @pin_y;
			return;
		}

		var i = @constraints.length;
		while(i--) @constraints[i].resolve();

		@x > boundsx ? @x = 2 * boundsx - @x : 1 > @x && (@x = 2 - @x);
		@y < 1 ? @y = 2 - @y : @y > boundsy && (@y = 2 * boundsy - @y);
	},

	attach = function(point) {
		@constraints.push(
			Constraint(this, point)
		);
	},

	remove_constraint = function(lnk) {
		var i = @constraints.length;
		while(i--) if(@constraints[i] == lnk) @constraints.splice(i, 1);
	},

	add_force = function(x, y )  {
		@vx += x;
		@vy += y;
	},

	pin = function(pinx, piny) {
		@pin_x = pinx;
		@pin_y = piny;
	},
}

var Constraint = {
	__construct = function(p1, p2) {
		@p1 = p1;
		@p2 = p2;
		@length = spacing;
	},

	resolve = function() {
		var diff_x = @p1.x - @p2.x
		var diff_y = @p1.y - @p2.y
		var dist = Math.sqrt(diff_x * diff_x + diff_y * diff_y)
		var diff = (@length - dist) / dist

		if (dist > tear_distance) @p1.remove_constraint(this);

		var px = diff_x * diff * 0.5;
		var py = diff_y * diff * 0.5;

		@p1.x += px;
		@p1.y += py;
		@p2.x -= px;
		@p2.y -= py;
	},

	draw = function() {
		ctx.moveTo(@p1.x, @p1.y);
		ctx.lineTo(@p2.x, @p2.y);
	},
}

var Cloth = {
	__construct = function() {
		@points = [];

		var start_x = canvas.width / 2 - cloth_width * spacing / 2;
		for(var y = 0; y <= cloth_height; y++) {
			for(var x = 0; x <= cloth_width; x++) {
				var p = Point(start_x + x * spacing, start_y + y * spacing);

				y == 0 && p.pin(p.x, p.y);
				y != 0 && p.attach(@points[x + (y - 1) * (cloth_width + 1)]);
				x != 0 && p.attach(@points[@points.length - 1]);

				@points.push(p);
			}
		}
	},

	update = function() {
		for(var i = 0 ; i < physics_accuracy; i++){
			for(var _, p in @points){
				p.resolve_constraints();
			}
		}
		for(var _, p in @points){
			p.update(.016);
		}
	},

	draw = function(params) {
		for(var _, p in cloth.points){
			p.draw(params);
		}
	},
}

director.scene = (extends Scene {
	__construct = function(){
		@addEventListener("enterFrame", function(){
			cloth.update();
		})
	},
	
	paint = function(params){
		cloth.draw(params)
	},
})()
