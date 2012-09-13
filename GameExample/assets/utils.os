
function ccDrawPoly(points closePolygon fill)
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
	
	fromGL = function(m){
		this.a = m[0]; this.c = m[4]; this.tx = m[12];
		this.b = m[1]; this.d = m[5]; this.ty = m[13];
		return this
	}
}


Easy = {
	linear = function(t){
		return t
	}

	inQuad = function(t){
		return t * t
	}

	outQuad = function(t){
		return -t * (t - 2)
	}

	inOutQuad = function(t){
		return t < 0.5 ? t * t : ((1 - t) * (t - 3) - 1)
	}

	outInQuad = function(t){
		return t < 0.5 ? Easy.outQuad(t * 2) : Easy.inQuad(t * 2 - 1)
	}

	inCubic = function(t){
		return t * t * t
	}

	outCubic = function(t){
		t = t - 1
		return t * t * t + 1
	}

	inOutCubic = function(t){
		return t < 0.5 ? Easy.inCubic(t * 2) / 2 : Easy.outCubic(t * 2 - 1) / 2 + 0.5
	}

	outInCubic = function(t){
		return t < 0.5 ? Easy.outCubic(t * 2) / 2 : Easy.inCubic(t * 2 - 1) / 2 + 0.5
	}

	/*
	float EasyLib::InQuart(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t /= d;
		return c * t * t * t * t + b;
	}

	float EasyLib::OutQuart(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t = t / d - 1;
		return (0 - c) * (t * t * t * t - 1) + b;
	}

	float EasyLib::InOutQuart(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / (d / 2)) < 1) 
		{
			return c / 2 * t * t * t * t + b;
		}
		t -= 2;
		return (0 - c) / 2 * (t * t * t * t - 2) + b;
	}

	float EasyLib::OutInQuart(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutQuart(t * 2, b, c / 2, d);
		}
		return InQuart(t * 2 - d, b + c / 2, c / 2, d);
	}

	float EasyLib::InQuint(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t /= d;
		return c * t * t * t * t * t + b;
	}

	float EasyLib::OutQuint(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t = t / d - 1;
		return c * (t * t * t * t * t + 1) + b;
	}

	float EasyLib::InOutQuint(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / (d / 2)) < 1) 
		{
			return c / 2 * t * t * t * t * t + b;
		}
		t = t - 2;
		return c / 2 * (t * t * t * t * t + 2) + b;
	}

	float EasyLib::OutInQuint(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutQuint(t * 2, b, c / 2, d);
		}
		return InQuint(t * 2 - d, b + c / 2, c / 2, d);
	}

	float EasyLib::InExpo(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		return c * MathLib::Pow(2, 10 * (t / d - 1)) + b;
	}

	float EasyLib::OutExpo(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		return c * (0 - MathLib::Pow(2, -10 * t / d) + 1) + b;
	}

	float EasyLib::InOutExpo(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / (d / 2)) < 1) 
		{
			return c / 2 * MathLib::Pow(2, 10 * (t - 1)) + b;
		}
		return c / 2 * (0 - MathLib::Pow(2, -10 * --t) + 2) + b;
	}

	float EasyLib::OutInExpo(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutExpo(t * 2, b, c / 2, d);
		}
		return InExpo(t * 2 - d, b + c / 2, c / 2, d);
	}

	float EasyLib::InCirc(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t /= d;
		return (0 - c) * (MathLib::Sqrt(1 - t * t) - 1) + b;
	}

	float EasyLib::OutCirc(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t = t / d - 1;
		return c * MathLib::Sqrt(1 - t * t) + b;
	}

	float EasyLib::InOutCirc(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / (d / 2)) < 1) 
		{
			return (0 - c) / 2 * (MathLib::Sqrt(1 - t * t) - 1) + b;
		}
		t -= 2;
		return c / 2 * (MathLib::Sqrt(1 - t * t) + 1) + b;
	}

	float EasyLib::OutInCirc(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutCirc(t * 2, b, c / 2, d);
		}
		return InCirc(t * 2 - d, b + c / 2, c / 2, d);
	}

	float EasyLib::InBack(float t, float b, float c, float d, float s)
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t /= d;
		return c * t * t * ((s + 1) * t - s) + b;
	}

	float EasyLib::OutBack(float t, float b, float c, float d, float s)
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		t = t / d - 1;
		return c * (t * t * ((s + 1) * t + s) + 1) + b;
	}

	float EasyLib::InOutBack(float t, float b, float c, float d, float s)
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / (d / 2)) < 1) 
		{
			s *= 1.525f;
			return c / 2 * t * t * ((s + 1) * t - s) + b;
		}
		s *= 1.525f;
		t -= 2;
		return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
	}

	float EasyLib::OutInBack(float t, float b, float c, float d, float s)
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutBack(t * 2, b, c / 2, d, s);
		}
		return InBack(t * 2 - d, b + c / 2, c / 2, d, s);
	}

	float EasyLib::InBounce(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		return c - OutBounce(d - t, 0, c, d) + b;
	}

	float EasyLib::OutBounce(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if ((t = t / d) < 0.363636363636f) 
		{
			return c * 7.5625f * t * t + b;
		}
		if (t < 0.727272727273f) 
		{
			t -= 0.545454545455f;
			return c * (7.5625f * t * t + 0.75f) + b;
		}
		if (t < 0.909090909091f) 
		{
			t -= 0.818181818182f;
			return c * (7.5625f * t * t + 0.9375f) + b;
		}
		t -= 0.954545454545f;
		return c * (7.5625f * t * t + 0.984375f) + b;
	}

	float EasyLib::InOutBounce(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return InBounce(t * 2, 0, c, d) * 0.5f + b;
		}
		return OutBounce(t * 2 - d, 0, c, d) * 0.5f + c * 0.5f + b;
	}

	float EasyLib::OutInBounce(t){
	{
		if(t <= 0.0f)
		{
			return b;
		}
		if(t >= d)
		{
			return b + c;
		}
		if (t < d / 2) 
		{
			return OutBounce(t * 2, b, c / 2, d);
		}
		return InBounce(t * 2 - d, b + c / 2, c / 2, d);
	}
	*/
}
var Easy = Easy