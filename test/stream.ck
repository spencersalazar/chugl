
chugl gfx;
gfx.gl @=> OpenGL gl;

gfx.openWindow(512, 512);
gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;
Math.pow(2,0.5)*WIDTH => float DIAGONAL;

//-Math.pow(2/pi*Math.asin(Math.random2f(0,0.5)), 1.0/3.0)*pi/2 => float angle;
Math.random2f(-pi/16, -7*pi/16) => float angle;

fun void streamer()
{
    Math.random2f(0,DIAGONAL) => float height;
    Math.random2f(1, 6) => float thickness;
    Math.random2f(0,1) => float h1;
    Math.random2f(0.7,0.9) => float s1;
    Math.random2f(0.8,1.0) => float v1;
    Math.random2f(0,1) => float h2;
    Math.random2f(0.7,0.9) => float s2;
    Math.random2f(0.8,1.0) => float v2;
    Math.random2f(WIDTH/2, WIDTH*2) => float length;
    
    Math.random2f(-(DIAGONAL-WIDTH)-WIDTH/3, -(DIAGONAL-WIDTH)) => float pos;
    Math.random2f(3, 17) => float v;
    
    while(pos-length <= DIAGONAL)
    {
        gfx.pushMatrix();
        
        gfx.translate(WIDTH/2, HEIGHT/2);
        gfx.rotate(angle);
        gfx.translate(-WIDTH/2, -HEIGHT/2);
        
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
    spork ~ streamer();
    
    0.1::second => now;
}
