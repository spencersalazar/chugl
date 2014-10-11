
chugl gfx;

gfx.fullscreen();

gfx.width() => float WIDTH;
gfx.height() => float HEIGHT;

0.001 => float prob;
[-pi/4, pi/4] @=> float branches[];

Event doDraw;

fun void tree(float x, float y, float r, float g, float b, float angle)
{
    0 => float length;
    0 => int branched;
        
    while(true)
    {
        if(!branched && Math.random2f(0, 1) < prob)
        {
            1 => branched;
            prob*0.2 -=> prob;
            for(int i; i < branches.size(); i++)
                spork ~ tree(x-length*Math.sin(angle), y+length*Math.cos(angle), r, g, b, angle+branches[i]);
        }
        
        gfx.color(r, g, b, 1);
        gfx.pushMatrix();
        gfx.translate(x, y);
        gfx.rotate(angle);
        gfx.line(0, 0, 0, length);
        gfx.popMatrix();
        
        if(!branched)
            1.0 +=> length;
        
        doDraw => now;
    }
}

spork ~ tree(WIDTH/2, 0, 1, 0, 0, 0);

while(true)
{
    gfx.clear();
    
    prob*0.01 +=> prob;
    
    doDraw.broadcast();
    me.yield();
    
    (1.0/60.0)::second => now;
}
