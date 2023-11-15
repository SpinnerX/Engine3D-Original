# Logging System Notes
- Logging to monitor information on systems we are running
- Whether certain things work or not
- Mentions if any files were opened successfully or not
- Such things like if shaders compiled successfully or not.

# Creating our own logging system for an engine specific use
- Should create a logging system that macrifies the and abstracts the logging away
- Logging code shouldn't be present in the client code, rather thhe engine code specifically.

## Added Functionality
- Added EngineLogger.h
- Allowed creating different two instances for logging, client and game engine.
- Allowing to create different instances of logging to log to different logging entities.
- For future reference. May want to have a way of uniquely identifying where we ant to log too.
- For example here is how we log to coreLogger and clientLogger
- Example: coreLogError("Message") and clientLogError("Message")
- Instead of doing it that way, we may want to do something like
- Example: logError("console", message); and when we initate the loggers
- In the init function would possibly be doing: std::make_shared<Logger::Log>("GameEngine") or looking into another way of doing this.
