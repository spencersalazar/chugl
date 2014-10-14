// sporking + rendering test

chugl gfx;
gfx.gl @=> OpenGL @ gl;

gfx.openWindow(512, 512);

gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;


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

spork ~ flare();
spork ~ flare();
spork ~ flare();
spork ~ flare();

while(true) 1::second => now;

fun void flare()
{
    Std.rand2f(0, WIDTH) => float x;
    Std.rand2f(0, HEIGHT) => float y;
    Std.rand2f(0, 180) => float phase;
    
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
        
        if(Std.rand2f(0,1) < 0.0025)
            spork ~ flare();
        if(Std.rand2f(0,1) < 0.00125)
            break;
        
        gl.PushMatrix();

        gl.Enable(gl.BLEND);
        //gl.BlendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
        gl.BlendFunc(gl.SRC_ALPHA, gl.ONE);
        
        gl.Color4f(1.0, 0.0, 0.0, c.val()*0.83);
        gl.DisableClientState(gl.COLOR_ARRAY);
        
        gl.Translatef(x, y, 0.0);
        gl.Rotatef(phase+now/second*180, 0, 0, 1);
        
        gl.VertexPointer(2, gl.DOUBLE, 0, geo);
        gl.EnableClientState(gl.VERTEX_ARRAY);
        
        gl.Enable(gl.TEXTURE_2D);
        gl.BindTexture(gl.TEXTURE_2D, img.tex());
        gl.TexCoordPointer(2, gl.DOUBLE, 0, texcoord);
        gl.EnableClientState(gl.TEXTURE_COORD_ARRAY);
        
        gl.DrawArrays(gl.TRIANGLE_STRIP, 0, 4);
        
        gl.PopMatrix();
        
        (1.0/60.0)::second => now;
    }
    
    while(true) 1::second => now;
}
    
