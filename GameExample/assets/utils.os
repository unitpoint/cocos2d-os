
function ccDrawPoly(points closePolygon fill)
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

	// save to local var to prevent dealocation by gc
	var pointer = glVertexPointer(2, GL_FLOAT, 0, points);
    if(closePolygon){
        glDrawArrays(fill && GL_TRIANGLE_FAN || GL_LINE_LOOP, 0, #points);
	}else{
		glDrawArrays(fill && GL_TRIANGLE_FAN || GL_LINE_STRIP, 0, #points);
	}

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
}

Matrix = {
	/* __object = {
		a = 1 b = 0
		c = 0 d = 1
		tx = 0 ty = 0
	} */
	
	__construct = function(a b c d tx ty){
		if(!a){
			this.a = 1
			this.b = 0
			this.c = 0
			this.d = 1
			this.tx = 0
			this.ty = 0
			return
		}
		this.a = a
		this.b = b
		this.c = c
		this.d = d
		this.tx = tx
		this.ty = ty
	}
	
	set = function(a b c d tx ty){
		if(!a){
			this.a = 1
			this.b = 0
			this.c = 0
			this.d = 1
			this.tx = 0
			this.ty = 0
			return
		}
		this.a = a
		this.b = b
		this.c = c
		this.d = d
		this.tx = tx
		this.ty = ty
		return this
	}
	
	transform = function(point){
		return {
			x = this.a * point.x + this.c * point.y + this.tx
			y = this.b * point.x + this.d * point.y + this.ty
		}
	}
	
	translate = function(tx ty){
		return this.set(this.a, this.b, this.c, this.d, this.tx + this.a * tx + this.c * ty, this.ty + this.b * tx + this.d * ty)
	}

	scale = function(sx sy){
		return this.set(this.a * sx, this.b * sx, this.c * sy, this.d * sy, this.tx, this.ty)
	}
	
	rotate = function(angle){
		angle = math.rad(angle)
		var fSin = math.sin(angle);
		var fCos = math.cos(angle);
		var t = this
		return this.set(this.a * fCos + this.c * fSin,
			this.b * fCos + this.d * fSin,
			this.c * fCos - this.a * fSin,
			this.d * fCos - this.b * fSin,
			this.tx, this.ty)
	}
	
	skew = function(skewX skewY){
		var skewMatrix = Matrix(1.0, math.tan(math.rad(skewY)), math.tan(math.rad(skewX)), 1.0, 0.0, 0.0)
		return skewMatrix.mult(this)
	}
	
	mult = function(t2){
		var t1 = this
		return this.set(
			t1.a * t2.a + t1.b * t2.c, t1.a * t2.b + t1.b * t2.d, //a,b
			t1.c * t2.a + t1.d * t2.c, t1.c * t2.b + t1.d * t2.d, //c,d
			t1.tx * t2.a + t1.ty * t2.c + t2.tx,				  //tx
			t1.tx * t2.b + t1.ty * t2.d + t2.ty)				  //ty
	}

	inverse = function(){
		var determinant = 1 / (this.a * this.d - this.b * this.c)
		return this.set(determinant * this.d, -determinant * this.b, -determinant * this.c, determinant * this.a,
			determinant * (this.c * this.ty - this.d * this.tx), determinant * (this.b * this.tx - this.a * this.ty) )
	}
	
	toGL = function(){
		var m = []
		m[2], m[3], m[6], m[7] = 0, 0, 0, 0
		m[8], m[9], m[11], m[14] = 0, 0, 0, 0
		m[10], m[15] = 1, 1
		m[0] = this.a; m[4] = this.c; m[12] = this.tx;
		m[1] = this.b; m[5] = this.d; m[13] = this.ty;
		return m
	}
	
	setFromGL = function(m){
		this.a = m[0]; this.c = m[4]; this.tx = m[12];
		this.b = m[1]; this.d = m[5]; this.ty = m[13];
		return this
	}
}
