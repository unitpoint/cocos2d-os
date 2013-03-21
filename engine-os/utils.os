
function ccDrawPoly(points, closePolygon, fill)
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

	// save to local var to prevent dealocation by gc
	var pointer = glVertexPointer(2, GL_FLOAT, 0, points);
    if(closePolygon){
        glDrawArrays(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, #points);
	}else{
		glDrawArrays(fill ? GL_TRIANGLE_FAN : GL_LINE_STRIP, 0, #points);
	}

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
}

Matrix = {
	__construct = function(a, b, c, d, tx, ty){
		if(!a){
			@a = 1
			@b = 0
			@c = 0
			@d = 1
			@tx = 0
			@ty = 0
		}else{
			@a = a
			@b = b
			@c = c
			@d = d
			@tx = tx
			@ty = ty
		}
	},
	
	set = function(a, b, c, d, tx, ty){
		if(!a){
			@a = 1
			@b = 0
			@c = 0
			@d = 1
			@tx = 0
			@ty = 0
			return this
		}
		@a = a
		@b = b
		@c = c
		@d = d
		@tx = tx
		@ty = ty
		return this
	},
	
	transform = function(point){
		return {
			x = @a * point.x + @c * point.y + @tx,
			y = @b * point.x + @d * point.y + @ty,
		}
	},
	
	translate = function(tx, ty){
		return @set(@a, @b, @c, @d, @tx + @a * tx + @c * ty, @ty + @b * tx + @d * ty)
	},

	scale = function(sx, sy){
		return @set(@a * sx, @b * sx, @c * sy, @d * sy, @tx, @ty)
	},
	
	rotate = function(angle){
		angle = math.rad(angle)
		var fSin = math.sin(angle);
		var fCos = math.cos(angle);
		return @set(@a * fCos + @c * fSin,
			@b * fCos + @d * fSin,
			@c * fCos - @a * fSin,
			@d * fCos - @b * fSin,
			@tx, @ty)
	},
	
	skew = function(skewX, skewY){
		var skewMatrix = Matrix(1.0, math.tan(math.rad(skewY)), math.tan(math.rad(skewX)), 1.0, 0.0, 0.0)
		return skewMatrix.mult(this)
	},
	
	mult = function(t2){
		var t1 = this
		return @set(
			t1.a * t2.a + t1.b * t2.c, t1.a * t2.b + t1.b * t2.d, //a,b
			t1.c * t2.a + t1.d * t2.c, t1.c * t2.b + t1.d * t2.d, //c,d
			t1.tx * t2.a + t1.ty * t2.c + t2.tx,				  //tx
			t1.tx * t2.b + t1.ty * t2.d + t2.ty)				  //ty
	},

	inverse = function(){
		var determinant = 1 / (@a * @d - @b * @c)
		return @set(determinant * @d, -determinant * @b, -determinant * @c, determinant * @a,
			determinant * (@c * @ty - @d * @tx), determinant * (@b * @tx - @a * @ty) )
	},
	
	toGL = function(){
		return [
			@a, @b, 0, 0,
			@c, @d, 0, 0,
			 0,  0, 1, 0,
			@tx, @ty, 0, 1,
		]
		/* var m = []
		m[2], m[3], m[6], m[7] = 0, 0, 0, 0
		m[8], m[9], m[11], m[14] = 0, 0, 0, 0
		m[10], m[15] = 1, 1
		m[0] = @a; m[4] = @c; m[12] = @tx;
		m[1] = @b; m[5] = @d; m[13] = @ty;
		return m */
	},
	
	fromGL = function(m){
		@a = m[0]; @c = m[4]; @tx = m[12];
		@b = m[1]; @d = m[5]; @ty = m[13];
		return this
	},
}

Easy = {
	linear = {|t| t},
	inQuad = {|t| t * t},
	inCubic = {|t| t ** 3},
	inQuart = {|t| t ** 4},
	inQuint = {|t| t ** 5},
	inSine = {|t| 1 - math.cos(t * math.PI / 2)},
	inExpo = {|t| 2 ** (10 * (t - 1))},
	inCirc = {|t| 1 - (1 - t ** 2) ** 0.5},

	s = 1.70158,
	
	inBack = {|t|
		var s = Easy.s 
		return t * t * ((s + 1) * t - s)
	},

	inBounce = {|t| 1 - outBounce(1 - t)},
}

var Easy = Easy

var function outBounce(t){
	if(t < 0.363636363636f){
		return 7.5625f * t * t
	}
	if(t < 0.727272727273f) {
		t = t - 0.545454545455f
		return 7.5625f * t * t + 0.75f
	}
	if(t < 0.909090909091f) {
		t = t - 0.818181818182f
		return 7.5625f * t * t + 0.9375f
	}
	t = t - 0.954545454545f
	return 7.5625f * t * t + 0.984375f
}


var function easyInOutHelper(t, inFunc){
	return t <= 0.5 ? inFunc(t * 2) / 2 : 1 - inFunc(2 - t * 2) / 2
}

for(var name, func in Easy.clone()){
	if(functionOf(func) && name.sub(0, 2) == "in"){
		{|func|
			{|func|
				// Easy[name] = func
				name = name.sub(2)
				Easy["out"..name] = {|t| 1 - func(1 - t)}
				Easy["inOut"..name] = {|t| easyInOutHelper(t, func)}
				Easy["outIn"..name] = {|t| 1 - easyInOutHelper(1 - t, func)}
			}{|t| func(t < 0 ? 0 : t > 1 ? 1 : t)}
		}(func)
	}
}
