#include "Configuration.h"
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include <thread>
#include <vector>
#include <iostream>
#include <memory> // לשימוש ב-std::unique_ptr

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    try {
        // קריאת הקונפיגורציה
        Configuration config(argv[1]);

        // יצירת תורים למפיקים
        std::vector<std::unique_ptr<BoundedBuffer>> producerQueues; // רשימת תורים דינמיים
        std::vector<Producer> producers; // רשימת מפיקים

        for (const auto& producerConfig : config.getProducers()) {
            // יצירת תור דינמי עבור המפיק
            producerQueues.emplace_back(std::make_unique<BoundedBuffer>(producerConfig.queueSize));
            // יצירת המפיק עם הפניה לתור שלו
            producers.emplace_back(producerConfig.id, producerConfig.numMessages, *producerQueues.back());
        }

        // יצירת תורים לעורכים
        BoundedBuffer sportsQueue(config.getCoEditorQueueSize());
        BoundedBuffer newsQueue(config.getCoEditorQueueSize());
        BoundedBuffer weatherQueue(config.getCoEditorQueueSize());

        // יצירת התור המשותף למנהל המסך
        BoundedBuffer sharedQueue(config.getCoEditorQueueSize());

        // יצירת Co-Editors
        CoEditor sportsEditor("SPORTS", sportsQueue, sharedQueue);
        CoEditor newsEditor("NEWS", newsQueue, sharedQueue);
        CoEditor weatherEditor("WEATHER", weatherQueue, sharedQueue);

        // יצירת רשימת מצביעים לתורי המפיקים עבור ה-Dispatcher
        std::vector<BoundedBuffer*> producerQueuePtrs;
        for (auto& queue : producerQueues) {
            producerQueuePtrs.push_back(queue.get());
        }

        // יצירת Dispatcher
        Dispatcher dispatcher(producerQueuePtrs, sportsQueue, newsQueue, weatherQueue);

        // יצירת Screen Manager
        ScreenManager screenManager(sharedQueue);

        // Threads למפיקים
        std::vector<std::thread> producerThreads;
        for (auto& producer : producers) {
            producerThreads.emplace_back(&Producer::produce, &producer);
        }

        // Thread ל-Dispatcher
        std::thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

        // Threads ל-Co-Editors
        std::thread sportsThread(&CoEditor::edit, &sportsEditor);
        std::thread newsThread(&CoEditor::edit, &newsEditor);
        std::thread weatherThread(&CoEditor::edit, &weatherEditor);

        // Thread למנהל המסך
        std::thread screenThread(&ScreenManager::display, &screenManager);

        // המתנה לסיום כל ה-Threads
        for (auto& thread : producerThreads) {
            thread.join();
        }
        dispatcherThread.join();
        sportsThread.join();
        newsThread.join();
        weatherThread.join();
        screenThread.join();

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
