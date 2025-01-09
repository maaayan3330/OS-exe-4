#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "Configuration.h"
#include <iostream>
#include <vector>
#include <thread>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    // Parse the configuration file
    Configuration config;
    try {
        config = parseConfigurationFile(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    const int numProducers = config.producers.size();

    // Buffers for each producer
    std::vector<BoundedBuffer*> producerQueues;
    for (const auto& producerConfig : config.producers) {
        producerQueues.push_back(new BoundedBuffer(producerConfig.queueSize));
    }

    // Buffers for each message type
    BoundedBuffer sportsQueue(config.coEditorQueueSize);
    BoundedBuffer newsQueue(config.coEditorQueueSize);
    BoundedBuffer weatherQueue(config.coEditorQueueSize);

    // Shared queue for Screen Manager
    BoundedBuffer sharedQueue(config.coEditorQueueSize);

    // Create producers
    std::vector<std::thread> producerThreads;
    for (size_t i = 0; i < config.producers.size(); ++i) {
        producerThreads.emplace_back([&, i]() {
            Producer producer(i + 1, config.producers[i].numProducts, *producerQueues[i]);
            producer.produce();
        });
    }

    // Create dispatcher
    Dispatcher dispatcher(producerQueues, sportsQueue, newsQueue, weatherQueue, numProducers);
    std::thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

    // Create Co-Editors
    std::thread sportsEditor(&CoEditor::edit, CoEditor(sportsQueue, sharedQueue, "SPORTS"));
    std::thread newsEditor(&CoEditor::edit, CoEditor(newsQueue, sharedQueue, "NEWS"));
    std::thread weatherEditor(&CoEditor::edit, CoEditor(weatherQueue, sharedQueue, "WEATHER"));

    // Create Screen Manager
    ScreenManager screenManager(sharedQueue, 3);
    std::thread screenManagerThread(&ScreenManager::display, &screenManager);

    // Wait for all producers to finish
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // Wait for the dispatcher to finish
    dispatcherThread.join();

    // Wait for Co-Editors to finish
    sportsEditor.join();
    newsEditor.join();
    weatherEditor.join();

    // Wait for Screen Manager to finish
    screenManagerThread.join();

    // Clean up
    for (auto queue : producerQueues) {
        delete queue;
    }

    std::cout << "All producers, dispatcher, Co-Editors, and Screen Manager have finished.\n";
    return 0;
}
