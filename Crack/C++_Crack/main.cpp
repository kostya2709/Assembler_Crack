#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>

using std::vector;

class Abstract_Field : public sf::RectangleShape
{
public:
    Abstract_Field (void);
    Abstract_Field (float x, float y, float width, float height, sf::Color color);

    sf::Texture texture;

    virtual int handle_Mouse_Pressed (void) {};
    virtual bool is_on_Mouse (float x, float y);
    virtual void render (sf::RenderWindow& window);
};

Abstract_Field::Abstract_Field (void)
{
    this->setPosition (sf::Vector2f (0, 0));
    this->setSize (sf::Vector2f (100, 100));
    this->setFillColor (sf::Color (0, 0, 0, 255));
}

Abstract_Field::Abstract_Field (float x, float y, float width, float height, sf::Color color)
{
    this->setPosition (sf::Vector2f (x, y));
    this->setSize (sf::Vector2f (width, height));
    this->setFillColor (color);
}

bool Abstract_Field::is_on_Mouse (float x, float y)
{
    sf::Vector2f pos = this->getPosition();
    sf::Vector2f size = this->getSize();
    
    if ((x >= pos.x) && (x <= pos.x + size.x) && (y >= pos.y) && (y <= pos.y + size.y))
        return 1;
}

void Abstract_Field::render (sf::RenderWindow& window)
{
    window.draw (*this);
}

class Manager : public Abstract_Field 
{
public:
    Manager (void) 
    : Abstract_Field (){}

    Manager (int number) 
    : Abstract_Field (){array.reserve (number);}

    Manager (float x, float y, float width, float height, sf::Color color, int number) 
    : Abstract_Field (x, y, width, height, color)
    {
        array.reserve (number);
    }

    vector <Abstract_Field*> array;

    //virtual int handle_Mouse_Pressed (void) override;
    virtual bool is_on_Mouse (float x, float y) override;
    virtual void render (sf::RenderWindow& window);

    ~Manager () {}
};

bool Manager::is_on_Mouse (float x, float y)
{
    sf::Vector2f pos = this->getPosition();
    sf::Vector2f size = this->getSize();
    
    if (!((x >= pos.x) && (x <= pos.x + size.x) && (y >= pos.y) && (y <= pos.y + size.y)))
        return 0;

    int num = this->array.size();
    int found = 0;

    for (int i = 0; i < num; ++i)
        if (this->array[i]->is_on_Mouse (x, y))
        {
            this->array[i]->handle_Mouse_Pressed();
            ++found;
        }
    
    if (found == 0)
        printf ("YOU MISSED!\n\n");

    return found;
}

void Manager::render (sf::RenderWindow& window)
{
    int size = this->array.size();
    int counter = 0;

    window.draw (*this);
    for (; counter < size; ++counter)
        this->array[counter]->render(window);
}

class Button_Overflow : public Abstract_Field
{
public:
    Button_Overflow (float x, float y, float width, float height, sf::Color color)
    :Abstract_Field (x, y, width, height, color) {}
    
    virtual int handle_Mouse_Pressed (void)override;
};

int Button_Overflow::handle_Mouse_Pressed (void)
{
    printf ("His buffer is only 10 symbols long. He expects '*' in the 11-th symbol.\n\n");
}

class Button_Register : public Abstract_Field
{
public:
    Button_Register (float x, float y, float width, float height, sf::Color color)
    :Abstract_Field (x, y, width, height, color) {}
    
    virtual int handle_Mouse_Pressed (void)override;
    //virtual bool is_on_Mouse (void) override;
};

int Button_Register::handle_Mouse_Pressed (void)
{
    printf ("Register\n");
    unsigned long long size = 0;
    const char* input = "../Ana_prog/suprogram.com";
    const char* output = "../Ana_prog/suprogram_cracked1.com";

    FILE* f_in = fopen (input, "rb");
    fseek (f_in, 0, SEEK_END);
    size = ftell (f_in);

    fseek (f_in, 0, SEEK_SET);
    char* buffer = (char*)calloc (size, 1);
    fread (buffer, 1, size, f_in);
    fclose (f_in);

    FILE* f_out = fopen (output, "wb");

    int offset1 = 0x1FA;
    int offset2 = 0x202;

    char test = 0;
    char new_byte = 0;

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been cracked in this way:( \n\n");
        free (buffer);
        fclose (f_out);
        return 1;
    }

    buffer[offset1] = new_byte;
    buffer[offset2] = new_byte;

    printf ("Hoooray, I have on_cracked it!\n\n");

    fwrite (buffer, 1, size, f_out);
    fclose (f_out);
    free (buffer);
    
    return 0;
}

class Button_jnz : public Abstract_Field
{
public:
    Button_jnz (float x, float y, float width, float height, sf::Color color)
    :Abstract_Field (x, y, width, height, color) {}

    virtual int handle_Mouse_Pressed (void)override;
    //virtual bool is_on_Mouse (void) override;
};

int Button_jnz::handle_Mouse_Pressed (void)
{
    printf ("jnz\n");

    unsigned long long size = 0;
    const char* input = "../Ana_prog/suprogram.com";
    const char* output = "../Ana_prog/suprogram_cracked2.com";

    FILE* f_in = fopen (input, "rb");
    fseek (f_in, 0, SEEK_END);
    size = ftell (f_in);

    fseek (f_in, 0, SEEK_SET);
    char* buffer = (char*)calloc (size, 1);
    fread (buffer, 1, size, f_in);
    fclose (f_in);

    FILE* f_out = fopen (output, "wb");

    int offset1 = 0x1E7;
    int offset2 = 0x1E8;

    char test = 0;
    char new_byte = 0x90;       //nop opcode

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been cracked in this way:( \n\n");
        fclose (f_out);
        free (buffer);
        return 1;
    }

    buffer[offset1] = new_byte;
    buffer[offset2] = new_byte;

    printf ("Hoooray, I have on_cracked it!\n\n");

    fwrite (buffer, 1, size, f_out);
    fclose (f_out);

    return 0;

}

class Button_Address : public Abstract_Field
{
public:
    Button_Address (float x, float y, float width, float height, sf::Color color)
    :Abstract_Field (x, y, width, height, color) {}
    
    virtual int handle_Mouse_Pressed (void)override;
    //virtual bool is_on_Mouse (void) override;
};

int Button_Address::handle_Mouse_Pressed (void)
{
    printf ("address\n");

    unsigned long long size = 0;
    const char* input = "../Ana_prog/suprogram.com";
    const char* output = "../Ana_prog/suprogram_cracked3.com";

    FILE* f_in = fopen (input, "rb");
    fseek (f_in, 0, SEEK_END);
    size = ftell (f_in);

    fseek (f_in, 0, SEEK_SET);
    char* buffer = (char*)calloc (size, 1);
    fread (buffer, 1, size, f_in);
    fclose (f_in);

    FILE* f_out = fopen (output, "wb");

    int offset1 = 0xDA;

    char test = 0;
    char new_byte = 0;       //nop opcode

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been cracked in this way:( \n\n");
        fclose (f_out);
        free (buffer);
        return 1;
    }

    buffer[offset1] = new_byte;

    printf ("Hoooray, I have on_cracked it!\n\n");

    fwrite (buffer, 1, size, f_out);
    fclose (f_out);

    return 0;
}

class Hacker
{
public:
    Hacker (void);
    Hacker (int width, int height);

    sf::RenderWindow window;
    Manager manager;

    void run (void);
    void render (void);
    void update (void);
    void handle_Events (void);
};

Hacker::Hacker (void) : window (sf::VideoMode (1000, 800), "Mom's hacker")
{
    this->window.setPosition (sf::Vector2i (600, 150));
    this->manager = *(new Manager(50, 50, 900, 600, sf::Color::Blue, 4));
}

Hacker::Hacker (int width, int height) : window (sf::VideoMode (width, height), "Mom's hacker")
{
    this->window.setPosition (sf::Vector2i (600, 150));
    this->manager = *(new Manager(50, 50, 600, 300, sf::Color::Blue, 4));
}

void Hacker::update (void)
{

}

void Hacker::render (void)
{
    this->window.clear (sf::Color(0, 204, 204, 255));
    
    this->manager.render (this->window);
    
    this->window.display();
}

void Hacker::handle_Events (void)
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                this->manager.is_on_Mouse (event.mouseButton.x, event.mouseButton.y);
            break;
            
            case sf::Event::Closed:
                this->window.close();
            break;
        }
    }
}

void Hacker::run (void)
{

    while (this->window.isOpen())
    {
        this->handle_Events();
        this->update();
        this->render();
    }
}


int Change_Byte (const char* file_out);
int Change_al (const char* buffer);
int Change_jnz (const char* buffer);
int Change_address (char* buffer);

int main()
{
    //Change_Byte (file_name3);
    Hacker hacker;
    
    Button_jnz btn1 (100, 100, 200, 200, sf::Color::Red);
    hacker.manager.array.push_back (&btn1);

    Button_Register btn2 (400, 100, 200, 200, sf::Color::Yellow);
    hacker.manager.array.push_back (&btn2);

    Button_Address btn3 (700, 100, 200, 200, sf::Color::Green);
    hacker.manager.array.push_back (&btn3);

    Button_Overflow btn4 (400, 400, 200, 200, sf::Color::Magenta);
    hacker.manager.array.push_back (&btn4);

    hacker.run();
}
/*
int Change_Byte (const char* file_out)
{


    f = fopen (file_out, "wb");

    if (Change_address (buffer))
        return 1;

    printf ("Hoooray, I have on_cracked it!\n");

    fwrite (buffer, 1, size, f);
    fclose (f);

    return 0;
}

int Change_al (char* buffer)
{
    int offset1 = 0x1FA;
    int offset2 = 0x202;

    char test = 0;
    char new_byte = 0;

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been on_Mouseed in this way:( \n");
        return 1;
    }

    buffer[offset1] = new_byte;
    buffer[offset2] = new_byte;

    return 0;
}

int Change_jnz (char* buffer)
{
    int offset1 = 0x1E7;
    int offset2 = 0x1E8;

    char test = 0;
    char new_byte = 0x90;       //nop opcode

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been on_Mouseed in this way:( \n");
        return 1;
    }

    buffer[offset1] = new_byte;
    buffer[offset2] = new_byte;

    return 0;
}

int Change_address (char* buffer)
{
    int offset1 = 0xDA;

    char test = 0;
    char new_byte = 0;       //nop opcode

    test = buffer[offset1];
 
    if (test == new_byte)
    {
        printf ("This program has already been on_Mouseed in this way:( \n");
        return 1;
    }

    buffer[offset1] = new_byte;

    return 0;
}
*/