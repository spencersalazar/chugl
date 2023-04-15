
chugl gfx;
gfx.gl @=> OpenGL gl;

//gfx.openWindow(512, 512);
gfx.fullscreen();
gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;
Math.pow(2,0.5)*WIDTH => float DIAGONAL;
2.4 => float ASPECT;
WIDTH/ASPECT => float FRAME_HEIGHT;
(HEIGHT-FRAME_HEIGHT)/2 => float LETTERBOX_HEIGHT;

//-Math.pow(2/pi*Math.asin(Math.random2f(0,0.5)), 1.0/3.0)*pi/2 => float angle;
Math.random2f(-pi/16, -7*pi/16) => float angle;

fun void streamer()
{
    Math.random2f(0, DIAGONAL) => float height;
    Math.random2f(0.5, 5) => float thickness;
    Math.pow(thickness/0.5,4) => float alpha;
    Math.random2f(0, 1) => float h1;
    Math.random2f(0.7, 0.9) => float s1;
    Math.random2f(0.8, 1.0) => float v1;
    Math.random2f(0, 1) => float h2;
    Math.random2f(0.7, 0.9) => float s2;
    Math.random2f(0.8, 1.0) => float v2;
    WIDTH*Math.pow(2, Math.random2f(-2, 1)) => float length;
    
    Math.random2f(-(DIAGONAL-WIDTH)-WIDTH/3, -(DIAGONAL-WIDTH)) => float pos;
    //Math.random2f(3, 17)*5 => float v;
    5*Math.pow(3, Math.random2f(0,2.5)) => float v;
    
    while(pos-length <= DIAGONAL)
    {
        //gl.Enable( gl.POLYGON_SMOOTH );
        //gl.Hint( gl.POLYGON_SMOOTH_HINT, gl.NICEST );
        
        gl.Viewport(0, LETTERBOX_HEIGHT$int, WIDTH$int, FRAME_HEIGHT$int);
        
        gfx.pushMatrix();
        
        gfx.translate(-(DIAGONAL-WIDTH)/2, -(DIAGONAL-HEIGHT)/2);
        gfx.translate(DIAGONAL/2, DIAGONAL/2);
        gfx.rotate(angle);
        gfx.translate(-DIAGONAL/2, -DIAGONAL/2);
        
        gl.Begin(gl.QUADS);
        gfx.hsv(h1, s1, v1, 0.9); gl.Vertex3f(pos, height-thickness/2, 0);
        gfx.hsv(h1, s1, v1, 0.9); gl.Vertex3f(pos, height+thickness/2, 0);
        gfx.hsv(h2, s2, v2, 0.9); gl.Vertex3f(pos-length, height+thickness/2, 0);
        gfx.hsv(h2, s2, v2, 0.9); gl.Vertex3f(pos-length, height-thickness/2, 0);
        gl.End();
        
        gfx.popMatrix();
        
        (1.0/60.0)::second => now;
        
        v +=> pos;
    }
}

fun void background()
{
    Math.random2f(0,1) => float h1;
    Math.random2f(0.7,0.9) => float s1;
    Math.random2f(0.8,1.0) => float v1;
    h1+0.5 => float h2;
    if(h2 > 1.0) h2-1.0 => h2;
    Math.random2f(0.7,0.9) => float s2;
    Math.random2f(0.8,1.0) => float v2;
    
    Math.random2f(0,pi) => float rot;
    Math.random2f(0.001, 0.002) => float rot_v;
    
    while(true)
    {
        gl.Viewport(0, LETTERBOX_HEIGHT$int, WIDTH$int, FRAME_HEIGHT$int);
        
        gfx.pushMatrix();
        
        gfx.translate(WIDTH/2, HEIGHT/2);
        gfx.rotate(rot);
        
        gl.Begin(gl.QUADS);
        gfx.hsv(h1, s1, v1, 1.0); gl.Vertex3f(-DIAGONAL/2, -DIAGONAL/2, -0.1);
        gfx.hsv(h1, s1, v1, 1.0); gl.Vertex3f( DIAGONAL/2, -DIAGONAL/2, -0.1);
        gfx.hsv(h2, s2, v2, 1.0); gl.Vertex3f( DIAGONAL/2,  DIAGONAL/2, -0.1);
        gfx.hsv(h2, s2, v2, 1.0); gl.Vertex3f(-DIAGONAL/2,  DIAGONAL/2, -0.1);
        gl.End();
        
        gfx.popMatrix();
        
        (1.0/60.0)::second => now;
        
        rot_v +=> rot;
    }
}

spork ~ background();

while(true)
{
    Math.random2(0,4)*4 => int num;
    for(0 => int i; i < num; i++)
        spork ~ streamer();
    
    0.3::second => now;
}
