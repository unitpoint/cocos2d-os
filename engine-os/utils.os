
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
