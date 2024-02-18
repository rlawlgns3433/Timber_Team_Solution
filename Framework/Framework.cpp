#include "pch.h"
#include "Framework.h"

void Framework::Init(int width, int height, const std::string& name)
{
    srand(std::time(NULL));

    windowSize.x = width;
    windowSize.y = height;

    window.create(sf::VideoMode(windowSize.x, windowSize.y), name);

    //window.setFramerateLimit(60);

    SCENEMANAGER.Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = realDeltaTime = clock.restart();
        deltaTime *= timeScale;

        time += deltaTime;
        realTime += realDeltaTime;

        InputManager::Clear(); // Ű �Է� �ʱ�ȭ

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputManager::UpdateEvent(event); // Ű �Է� �̺�Ʈ ó��
        }

        //Update
        SCENEMANAGER.Update(GetDeltaTime());

        // Draw
        window.clear();
        SCENEMANAGER.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENEMANAGER.Release();
}