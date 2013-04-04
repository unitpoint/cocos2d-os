
function addStats(parent, offs){
	offs = offs || 20
	var color = [1.0, 1.0, 1.0, 1]
	var font = "arial-en-ru-16.fnt"
	var fps = Text("fps", font).attrs {
		anchor = {x=1.05, y=1.05},
		x = parent.width,
		y = parent.height - offs,
		color = color,
		// shadow = true,
	}.insertTo(parent)
	
	var gcAllocatedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05, y=1.05},
		x = fps.x,
		y = fps.y - fps.fontHeight*1.05*1,
		color = color,
		// shadow = true,
	}.insertTo(parent)
	
	var gcUsedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05, y=1.05},
		x = fps.x,
		y = fps.y - fps.fontHeight*1.05*3,
		color = color,
		// shadow = true,
	}.insertTo(parent)
	
	var gcCachedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05, y=1.05},
		x = fps.x,
		y = fps.y - fps.fontHeight*1.05*2,
		color = color,
		// shadow = true,
	}.insertTo(parent)
	
	var gcNumObjects = Text("0", font).attrs{
		anchor = {x=1.05, y=1.05},
		x = fps.x,
		y = fps.y - fps.fontHeight*1.05*4,
		color = color,
		// shadow = true,
	}.insertTo(parent)
	
	parent.setTimeout(function(){
		fps.string = sprintf("%.1f fps", 1 / director.deltaTime)
		gcAllocatedBytes.string = sprintf("%d Kb allocated", GC.allocatedBytes / 1024)
		gcUsedBytes.string = sprintf("%d Kb used", (GC.allocatedBytes - GC.cachedBytes) / 1024)
		gcCachedBytes.string = sprintf("%d Kb cached", GC.cachedBytes / 1024)
		gcNumObjects.string = sprintf("%d gc objects", GC.numObjects)
	}, 0.3, true)
}

