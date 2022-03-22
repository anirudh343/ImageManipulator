// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
using namespace std;
#include <iomanip>
#include <string>
#include <vector>
#include "Stuff.h"


void GetData(string filepath, vector<Pixel>& Pixels, Header& header) {

    ifstream infile(filepath, ios_base::binary);

    infile.read((char*)&(header.idLength), 1);
    infile.read((char*)&(header.colorMapType), 1);
    infile.read((char*)&(header.dataTypeCode), 1);
    infile.read((char*)&(header.colorMapOrigin), 2);
    infile.read((char*)&(header.colorMapLength), 2);
    infile.read((char*)&(header.colorMapDepth), 1);
    infile.read((char*)&(header.xOrigin), 2);
    infile.read((char*)&(header.yOrigin), 2);
    infile.read((char*)&(header.width), 2);
    infile.read((char*)&(header.height), 2);
    infile.read((char*)&(header.bitsPerPixel), 1);
    infile.read((char*)&(header.imageDescriptor), 1);

    int tempcount = (header.width) * (header.height);
    Pixel temp;
    for (int i = 0; i < tempcount; i++)
    {
        infile.read((char*)&(temp.B), 1);
        infile.read((char*)&(temp.G), 1);
        infile.read((char*)&(temp.R), 1);
        Pixels.push_back(temp);
    }
    infile.close();
}

void newfile(string filepath, vector<Pixel>& Pixels, Header& header) {

    ofstream infile(filepath, ios_base::binary);

    infile.write((char*)&(header.idLength), 1);
    infile.write((char*)&(header.colorMapType), 1);
    infile.write((char*)&(header.dataTypeCode), 1);
    infile.write((char*)&(header.colorMapOrigin), 2);
    infile.write((char*)&(header.colorMapLength), 2);
    infile.write((char*)&(header.colorMapDepth), 1);
    infile.write((char*)&(header.xOrigin), 2);
    infile.write((char*)&(header.yOrigin), 2);
    infile.write((char*)&(header.width), 2);
    infile.write((char*)&(header.height), 2);
    infile.write((char*)&(header.bitsPerPixel), 1);
    infile.write((char*)&(header.imageDescriptor), 1);

    int tempcount = (header.width) * (header.height);

    for (int i = 0; i < tempcount; i++)
    {
        infile.write((char*)&(Pixels[i].B), 1);
        infile.write((char*)&(Pixels[i].G), 1);
        infile.write((char*)&(Pixels[i].R), 1);
    }
    infile.close();
}

        

int main()
{   
    //Task 1 -----------------------------------------------------
    vector<Pixel> layer1;
    Header layer1h;
    vector<Pixel> pattern1;
    Header pattern1h;
    GetData("input/layer1.tga", layer1, layer1h);
    GetData("input/pattern1.tga", pattern1, pattern1h);
    int tempcount = (layer1h.width) * (layer1h.height);
    Pixel temp;
    vector<Pixel> part1;
    for (int i = 0; i < tempcount; i++)
    {
        temp.B = ((float)(pattern1[i].B) * (float)(layer1[i].B) / 255) + (float)(0.5);
        temp.G = ((float)(pattern1[i].G) * (float)(layer1[i].G) / 255) + (float)(0.5);
        temp.R = ((float)(pattern1[i].R) * (float)(layer1[i].R) / 255) + (float)(0.5);
        part1.push_back(temp);
    }
    newfile("output/part1.tga", part1, layer1h);

    //Task 2 -----------------------------------------------------
    vector<Pixel> layer2;
    Header layer2h;
    vector<Pixel> car;
    Header carh;
    GetData("input/layer2.tga", layer2, layer2h);
    GetData("input/car.tga", car, carh);
    tempcount = (layer2h.width) * (layer2h.height);
    vector<Pixel> part2;
    for (int i = 0; i < tempcount; i++)
    {
        if (car[i].B < layer2[i].B) 
        {
            temp.B = 0;
        }
        else    
        {
            temp.B = car[i].B - layer2[i].B;
        }

        if (car[i].G < layer2[i].G)
        {
            temp.G = 0;
        }
        else
        {
            temp.G = car[i].G - layer2[i].G;
        }

        if (car[i].R < layer2[i].R)
        {
            temp.R = 0;
        }
        else
        {
            temp.R = car[i].R - layer2[i].R;
        }
        part2.push_back(temp);
    }
    newfile("output/part2.tga", part2, carh);

    //Task 3 -----------------------------------------------------
    vector<Pixel> pattern2;
    Header pattern2h;
    vector<Pixel> text;
    Header texth;
    GetData("input/pattern2.tga", pattern2, pattern2h);
    GetData("input/text.tga", text, texth);
    tempcount = (layer1h.width) * (layer1h.height);
    Pixel temp2;
    vector<Pixel> part3;
    for (int i = 0; i < tempcount; i++)
    {
        temp2.B = ((float)(pattern2[i].B) * (float)(layer1[i].B) / 255) + (float)(0.5);
        temp2.G = ((float)(pattern2[i].G) * (float)(layer1[i].G) / 255) + (float)(0.5);
        temp2.R = ((float)(pattern2[i].R) * (float)(layer1[i].R) / 255) + (float)(0.5);

        temp.B = ((1 - ((1 - ((float)(text[i].B) / 255)) * (1 - ((float)(temp2.B) / 255)))) * 255) + (float)(0.5);
        temp.G = ((1 - ((1 - ((float)(text[i].G) / 255)) * (1 - ((float)(temp2.G) / 255)))) * 255) + (float)(0.5);
        temp.R = ((1 - ((1 - ((float)(text[i].R) / 255)) * (1 - ((float)(temp2.R) / 255)))) * 255) + (float)(0.5);
        part3.push_back(temp);
    }
    newfile("output/part3.tga", part3, layer1h);

    //Task 4 -----------------------------------------------------
    vector<Pixel> circles;
    Header circlesh;
    GetData("input/circles.tga", circles, circlesh);
    tempcount = (layer2h.width) * (layer2h.height);
    vector<Pixel> part4;
    for (int i = 0; i < tempcount; i++)
    {
        temp2.B = ((float)(layer2[i].B) * (float)(circles[i].B) / 255) + (float)(0.5);
        temp2.G = ((float)(layer2[i].G) * (float)(circles[i].G) / 255) + (float)(0.5);
        temp2.R = ((float)(layer2[i].R) * (float)(circles[i].R) / 255) + (float)(0.5);

        if (temp2.B < pattern2[i].B)
        {
            temp.B = 0;
        }
        else
        {
            temp.B = temp2.B - pattern2[i].B;
        }

        if (temp2.G < pattern2[i].G)
        {
            temp.G = 0;
        }
        else
        {
            temp.G = temp2.G - pattern2[i].G;
        }

        if (temp2.R < pattern2[i].R)
        {
            temp.R = 0;
        }
        else
        {
            temp.R = temp2.R - pattern2[i].R;
        }
        part4.push_back(temp);
    }
    newfile("output/part4.tga", part4, layer2h);

    //Task 5 -----------------------------------------------------
    tempcount = (layer1h.width) * (layer1h.height);
    vector<Pixel> part5;
    for (int i = 0; i < tempcount; i++)
    {
        if (pattern1[i].B < 128)
        {
            if (((unsigned char)(2 * ((float)(pattern1[i].B) * (float)(layer1[i].B) / 255)) + (float)(0.5)) > (unsigned char)(255))
            {
                temp.B = 255;
            }
            else
            {
                temp.B = (2 * ((float)(pattern1[i].B) * (float)(layer1[i].B) / 255)) + (float)(0.5);
            }
        }
        else
        {
            if ((1 - (2 * ((1 - ((float)(pattern1[i].B) / 255)) * (1 - ((float)(layer1[i].B) / 255))))) < 0)
            {
                temp.B = 0;
            }
            else
            {
                temp.B = ((1 - (2 * ((1 - ((float)(pattern1[i].B) / 255)) * (1 - ((float)(layer1[i].B) / 255))))) * 255) + (float)(0.5);
            }
        }

        if (pattern1[i].G < 128)
        {
            if (((unsigned char)(2 * ((float)(pattern1[i].G) * (float)(layer1[i].G) / 255)) + (float)(0.5)) > (unsigned char)(255))
            {
                temp.G = 255;
            }
            else
            {
                temp.G = (2 * ((float)(pattern1[i].G) * (float)(layer1[i].G) / 255)) + (float)(0.5);
            }
        }
        else
        {
            if ((1 - (2 * ((1 - ((float)(pattern1[i].G) / 255)) * (1 - ((float)(layer1[i].G) / 255))))) < 0)
            {
                temp.G = 0;
            }
            else
            {
                temp.G = ((1 - (2 * ((1 - ((float)(pattern1[i].G) / 255)) * (1 - ((float)(layer1[i].G) / 255))))) * 255) + (float)(0.5);
            }
        }
      
        if (pattern1[i].R < 128)
        {
            if (((unsigned char)(2 * ((float)(pattern1[i].R) * (float)(layer1[i].R) / 255)) + (float)(0.5)) > (unsigned char)(255))
            {
                temp.R = 255;
            }
            else
            {
                temp.R = (2 * ((float)(pattern1[i].R) * (float)(layer1[i].R) / 255)) + (float)(0.5);
            }
        }
        else
        {
            if ((1 - (2 * ((1 - ((float)(pattern1[i].R) / 255)) * (1 - ((float)(layer1[i].R) / 255))))) < 0)
            {
                temp.R = 0;
            }
            else
            {
                temp.R = ((1 - (2 * ((1 - ((float)(pattern1[i].R) / 255)) * (1 - ((float)(layer1[i].R) / 255))))) * 255) + (float)(0.5);
            }
        }
        part5.push_back(temp);
    }
    newfile("output/part5.tga", part5, layer1h);

    //Task 6 ---------------------------------------------------
    tempcount = (carh.width) * (carh.height);
    vector<Pixel> part6;
    for (int i = 0; i < tempcount; i++)
    {
        temp.B = car[i].B;
        temp.R = car[i].R;

        if ((int)(car[i].G) + 200 > 255)
        {
            temp.G = 255;
        }
        else
        {
            temp.G = car[i].G + (unsigned char)(200);
        }

        part6.push_back(temp);
    }
    newfile("output/part6.tga", part6, carh);

    //Task 7 ---------------------------------------------------
    tempcount = (carh.width) * (carh.height);
    vector<Pixel> part7;
    for (int i = 0; i < tempcount; i++)
    {
        temp.G = car[i].G;
        temp.B = 0;

        if ((int)(car[i].R) * 4 > 255)
        {
            temp.R = 255;
        }
        else
        {
            temp.R = car[i].R * 4;
        }
        part7.push_back(temp);
    }
    newfile("output/part7.tga", part7, carh);

    //Task 8 ---------------------------------------------------
    vector<Pixel> part8b;
    vector<Pixel> part8g;
    vector<Pixel> part8r;
    tempcount = (carh.width) * (carh.height);
 
    for (int i = 0; i < tempcount; i++)
    {
        temp.G = car[i].G;
        temp.B = car[i].G;
        temp.R = car[i].G;
        part8g.push_back(temp);

        temp.G = car[i].B;
        temp.B = car[i].B;
        temp.R = car[i].B;
        part8b.push_back(temp);

        temp.G = car[i].R;
        temp.B = car[i].R;
        temp.R = car[i].R;
        part8r.push_back(temp);
    }
    newfile("output/part8_b.tga", part8b, carh);
   
    newfile("output/part8_g.tga", part8g, carh);
    
    newfile("output/part8_r.tga", part8r, carh);

    //Task 9 ---------------------------------------------------
    vector<Pixel> red;
    Header redh;
    vector<Pixel> blue;
    Header blueh;
    vector<Pixel> green;
    Header greenh;
    GetData("input/layer_red.tga", red, redh);
    GetData("input/layer_blue.tga", blue, blueh);
    GetData("input/layer_green.tga", green, greenh);
    tempcount = (redh.width) * (redh.height);
    vector<Pixel> part9;
    for (int i = 0; i < tempcount; i++)
    {
        temp.G = green[i].G;
        temp.B = blue[i].B;
        temp.R = red[i].R;
        part9.push_back(temp);
    }
    newfile("output/part9.tga", part9, redh);

    //Task 10 ---------------------------------------------------
    vector<Pixel> text2;
    Header text2h;
    GetData("input/text2.tga", text2, text2h);
    tempcount = (text2h.width) * (text2h.height);
    vector<Pixel> part10;
    for (int i = (tempcount - 1); i > -1; i--)
    {
        temp.G = text2[i].G;
        temp.B = text2[i].B;
        temp.R = text2[i].R;
        part10.push_back(temp);
    }
    newfile("output/part10.tga", part10, text2h);
   
    //Extra Credit ---------------------------------------------------
    
    vector<Pixel> extracredit;
    Header extracredith;
    extracredith = carh;
    extracredith.height = (carh.height) + (texth.height);
    extracredith.width = (carh.width) + (texth.width);

    for (int i = 0; i < (int)(carh.height); i++)
    {
        for (int j = i * 512; j < (i + 1) * (int)(texth.width); j++)
        {
            temp.G = text[j].G;
            temp.B = text[j].B;
            temp.R = text[j].R;
            extracredit.push_back(temp);
        }
        for (int k = i * 512; k < (i + 1) * (int)(texth.width); k++)
        {
            temp.G = pattern1[k].G;
            temp.B = pattern1[k].B;
            temp.R = pattern1[k].R;
            extracredit.push_back(temp);
        }
 
    }
    for (int i = 0; i < (int)(carh.height); i++)
    {
        for (int j = i * 512; j < (i + 1) * (int)(texth.width); j++)
        {
            temp.G = car[j].G;
            temp.B = car[j].B;
            temp.R = car[j].R;
            extracredit.push_back(temp);
        }
        for (int k = i * 512; k < (i + 1) * (int)(texth.width); k++)
        {
            temp.G = circles[k].G;
            temp.B = circles[k].B;
            temp.R = circles[k].R;
            extracredit.push_back(temp);
        }

    }
    newfile("output/extracredit.tga", extracredit, extracredith);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
