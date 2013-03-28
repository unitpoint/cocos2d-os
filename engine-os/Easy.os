
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
