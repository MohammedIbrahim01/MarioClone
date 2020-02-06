#ifndef UI_H
#define UI_H


#include <string>


class Ui
{
    enum DataIndex {UI_SCORE, UI_COINS, UI_TIME, UI_DATA_NUM};
    int uiData[UI_DATA_NUM] = {0, 0, 0};
    
    std::shared_ptr<sf::Font> font;
    std::vector<std::unique_ptr<sf::Text>> textVec;
    
public:
    void Init(std::string fileName)
    {
        font = std::make_unique<sf::Font>();
        font->loadFromFile(fileName);
        
        textVec.push_back(std::make_unique<sf::Text>());
        textVec.push_back(std::make_unique<sf::Text>());
        textVec.push_back(std::make_unique<sf::Text>());
        
        
        textVec[0]->setFont(*font);
        textVec[0]->setPosition(0,0);
        
        textVec[1]->setFont(*font);
        textVec[1]->setPosition(300,0);
        
        textVec[2]->setFont(*font);
        textVec[2]->setPosition(6000,0);
    }
    
    void Draw(sf::RenderWindow& window)
    {
        textVec[0]->setString("Score:\n" + std::to_string(uiData[UI_SCORE]));
        textVec[1]->setString("Coins:\n" + std::to_string(uiData[UI_COINS]));
        textVec[2]->setString("Time:\n" + std::to_string(uiData[UI_TIME]));
        
        for (auto& text : textVec)
            window.draw(*text);
    }
    
    void SetPosition(int x)
    {
        textVec[0]->setPosition(x, 0);
        textVec[1]->setPosition(x + 300, 0);
        textVec[2]->setPosition(x + 600, 0);
    }
    
    void IncreaseCoinsBy(int num)
    {
        uiData[UI_COINS] += num;
    }
    
    void IncreaseScoreBy(int num)
    {
        uiData[UI_SCORE] += num;
    }
    
    void IncreaseTimeBy(int num)
    {
        uiData[UI_TIME] += num;
    }
    
    int GetTime()
    {
        return uiData[UI_TIME];
    }
};

#endif

