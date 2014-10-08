// test OpenGL/chugl texture

512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;
gfx.gl @=> OpenGL @ gl;

gfx.openWindow(WIDTH, HEIGHT);

[-50.0, -50.0,
 50.0, -50.0,
-50.0,  50.0,
 50.0,  50.0 ]
@=> float geo[];

[0.0, 0.0, 
 1.0, 0.0, 
 0.0, 1.0,
 1.0, 1.0]
@=> float texcoord[];

chuglImage img;
img.load(me.dir()+"flare.png");

curveExp c;
0 => c.val;
1 => c.target;

while(true)
{
    if(c.target() == 1)
    {
        if(Std.rand2f(0,1) < 0.01)
            0 => c.target;
    }
    else if(c.target() == 0)
    {
        if(Std.rand2f(0,1) < 0.05)
            1 => c.target;
    }
    
    gfx.lock();
    gfx.beginDraw();
    
    gl.Clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    
    gl.Enable(gl.BLEND);
    gl.BlendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
    
    gl.Color4f(1.0, 0.0, 0.0, c.val());
    
    gl.Translatef(WIDTH/2, HEIGHT/2, 0.0);
    gl.Rotatef(now/second*180, 0, 0, 1);
    
    gl.VertexPointer(2, gl.FLOAT, 0, geo);
    gl.EnableClientState(gl.VERTEX_ARRAY);
    
    gl.Enable(gl.TEXTURE_2D);
    gl.BindTexture(gl.TEXTURE_2D, img.tex());
    gl.TexCoordPointer(2, gl.FLOAT, 0, texcoord);
    gl.EnableClientState(gl.TEXTURE_COORD_ARRAY);
    
    gl.DisableClientState(gl.COLOR_ARRAY);
    
    gl.DrawArrays(gl.TRIANGLE_STRIP, 0, 4);
    
    gfx.endDraw();
    gfx.unlock();
    
    (1.0/60.0)::second => now;
}

