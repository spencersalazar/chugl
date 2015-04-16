
512 => float WIDTH;
512 => float HEIGHT;

chugl gfx;

gfx.openWindow(WIDTH, HEIGHT);

me.arg(0) => Std.atoi => int num;
Math.max(1, num)$int => num;

for(0 => int i; i < num; i++)
    spork ~ shape();

while(true) 1::day => now;

fun void shape()
{
    Math.random2f(0,1) => float rot;
    
    while(true)
    {
        Math.random2(0, 3) => int shape;
        Math.random2f(50,250) => float width;
        Math.random2f(50,250) => float height;
        Math.random2f(0,1) => float hue;
        Math.random2f(0.25, 0.75) => float sat;
        Math.random2f(0.1,0.5) => float speed;
        if(maybe) -speed => speed;

        now + 2::second => time later;
        
        while(now < later)
        {
            gfx.pushMatrix();
            
            gfx.hsv(hue, sat, 0.75, 0.5);
            gfx.translate(WIDTH/2, HEIGHT/2);
            gfx.rotate(rot*2*pi);
            
            if(shape == 0)
                gfx.rect(-width/2, -height/2, width, height);
            else if(shape == 1)
                gfx.ellipse(0, 0, width/2, height/2);
            else if(shape == 2)
                gfx.line(-width/2, -height/2, width, height);
            else if(shape == 3)
                gfx.triangle(-width/2, -height/2, width/2, -height/2, 0, height/2);
            
            gfx.popMatrix();
            
            
            
            (1.0/60.0)::second => now;
            (1.0/60.0)*speed +=> rot;
        }
    }
}
