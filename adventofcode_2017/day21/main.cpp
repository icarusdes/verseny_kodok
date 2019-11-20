#include <iostream> 
#include <fstream>
#include <string>
#include <boost/regex.hpp>

struct block {
    uint size = 0; 
    uint newsize = 0; 
    char * from = NULL; 
    char * to = NULL; 

    bool isTransformed(block & sb, uint offset_x, uint offset_y) const  {
        // std::cout << __PRETTY_FUNCTION__  << std::endl;
        bool identical = true;         
        for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[i * size + j]) {
                    identical = false; 
                }
            }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[(size - 1 - i) + size * j]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[size * size - 1 - (i * size + j)]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[(size-1)*size - j * size + i]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[i * size + (size - 1 - j)]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[(size - 1 - i) * size + j ]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[(size - 1 - j) * size + (size - 1 - i) ]) {
                    identical = false; 
                }
            }
        }
        if (! identical) {
            identical = true; 
            for (int i = 0; i < size; i++) 
            for (int j = 0; j < size; j++) { 
                if (sb.from[sb.size * (offset_x * size + i ) + offset_y * size + j] != from[j * size + i ]) {
                    identical = false; 
                }
            }
        }
        if (identical) {
            // std::cout << "Ez mák volt " << std::endl;
            for (int i = 0; i < newsize; i++) 
            for (int j = 0; j < newsize; j++) { 
                sb.to[sb.newsize * (offset_x * newsize +i) + offset_y * newsize + j] = to[i * newsize + j];
            }
            return true; 
        }
        return false; 
    }

    void printBlock() const {
        uint pixelson = 0; 
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char pixel = from[i * size + j];
                std::cout << pixel; 
                if (pixel == '#')
                    pixelson++; 
            }
            std::cout << std::endl;
        }
        std::cout << "Number of pixels on is: " << pixelson << std::endl; 
    }
};

int main() {

    uint iterations = 18; 

    boost::regex shortline("([\\.#]+)/([\\.#]+) => ([\\.#]+)/([\\.#]+)/([\\.#]+).*");
    boost::regex longline("([\\.#]+)/([\\.#]+)/([\\.#]+) => ([\\.#]+)/([\\.#]+)/([\\.#]+)/([\\.#]+).*");
    boost::smatch matches;
    std::vector<block> blocks_two; 
    std::vector<block> blocks_three; 

    std::fstream input("input2.txt"); 
    std::string line;
    while (std::getline(input, line)) {
        block b;
        if (boost::regex_match(line, matches, shortline)) {
            std::cout << "shortline: " << line << std::endl;
            b.size = 2; 
            b.newsize = 3;
            b.from = new char[4]; 
            b.to   = new char[9];
            for (int i = 0; i < 4; i++) {
                b.from[i] = std::string(matches[1 + i / 2])[i%2];
            }
            for (int i = 0; i < 9; i++) {
                b.to[i] = std::string(matches[3 + i / 3])[i%3];
            }
            blocks_two.push_back(b);
        } else if (boost::regex_match(line, matches, longline)) {
            std::cout << "longline: " << line << std::endl;
            b.size = 3;
            b.newsize = 4; 
            b.from = new char[9]; 
            b.to   = new char[16];
            for (int i = 0; i < 9; i++) {
                b.from[i] = std::string(matches[1 + i / 3])[i%3];
            }
            for (int i = 0; i < 16; i++) {
                b.to[i] = std::string(matches[4 + i / 4])[i%4];
            }
            blocks_three.push_back(b);
        } else {
            std::cout << "Baj van " << line << std::endl;
            exit(0); 
        }
    }
    
    block image; 
    image.size = 3; 
    image.from = new char[9]; 
    strncpy(image.from, ".#...####", 9);
    image.printBlock();


    while (iterations--) {
        if (image.size % 2 == 0) {
            std::cout << "Image size is dividable with 2 - " << image.size << std::endl; 
            image.newsize = (image.size / 2) * 3; 
            image.to = new char[image.newsize * image.newsize]; 
            memset(image.to, '.', image.newsize * image.newsize * sizeof(char));

            for (int i = 0; i < image.size / 2; i++)
                for (int j = 0; j < image.size / 2; j++)  
                    for (const block & b : blocks_two) {
                        if (b.isTransformed(image, i, j)) 
                            break; 
                    }
            image.size = image.newsize; 

        } else if (image.size % 3 == 0) {
            std::cout << "Image size is dividable with 3 - " << image.size << std::endl; 
            image.newsize = (image.size / 3) * 4; 
            image.to = new char[image.newsize * image.newsize]; 
            memset(image.to, '.', image.newsize * image.newsize * sizeof(char));

            for (int i = 0; i < image.size / 3; i++)
                for (int j = 0; j < image.size / 3; j++)  
                    for (const block & b : blocks_three) {
                        if (b.isTransformed(image, i, j)) 
                            break; 
                    }

            image.size = image.newsize; 
        } else {
            std::cout << "Itt bizony baj van " << std::endl; 
            exit(0); 
        }
        delete[] image.from;
        image.from = image.to; 
        image.to = NULL; 
        image.printBlock();
    }

    return 0; 

}