class Bunny
{
    float x;
    float y;
    float speedX;
    float speedY;

    Bunny()
    {
        x = core::random(0, 840);
        y = core::random(0, 450);
        speedX = core::random(-256, 256) / 60.0;
        speedY = core::random(-256, 256) / 60.0;
    }

    void update()
    {
        x += speedX;
        y += speedY;

        if (x < 0 || x > 840)
        {
            speedX = -speedX;
        }
        if (y < 0 || y > 450)
        {
            speedY = -speedY;
        }
        graphics::render(1, x, y);
    }
}


void main() 
{
    print("Start");

    window::init(800,600,"Ray with anglescript");

    assets::load_texture(1, "wabbit_alpha.png");

    array<Bunny@> bunnies;

    while(!window::should_close())
    {

    if (mouse::down(0))
    {
        
         for (int i = 0; i < 100; i++)
        {
            Bunny@ bunny = Bunny();
            bunnies.insertLast(bunny);
        }
    }

        graphics::clear(0, 0, 45);
        graphics::begin();

         graphics::set_color(255, 255, 255);


         for (int i = 0; i < bunnies.length(); i++)
        {
            bunnies[i].update();
        }


        graphics::set_color(0,0,0);
        graphics::rectangle(5,5,150,60,false);
        graphics::set_color(255, 0, 0);
        graphics::show_fps(10, 10);
        graphics::set_text_size(20);
        graphics::text_int(10,40,bunnies.length());
        graphics::set_color(255, 255, 255);

         graphics::end();


    }

    window::close();

 

}
