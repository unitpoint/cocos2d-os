
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
