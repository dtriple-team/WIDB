#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

#include <touchgfx/Utils.hpp>
#include <touchgfx/Callback.hpp>

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:
    Model();
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();

    void setToggleButton1State(bool state);
    bool getToggleButton1State() const;
    void setToggleButton2State(bool state);
    bool getToggleButton2State() const;

    void setSlider1Value(int value); //test
    int getSlider1Value() const; //test

    touchgfx::GenericCallback<bool>& getToggleButton1StateChangedCallback() { return toggleButton1StateChangedCallback; }
    touchgfx::GenericCallback<bool>& getToggleButton2StateChangedCallback() { return toggleButton2StateChangedCallback; }

protected:
    ModelListener* modelListener;
    int tickCounter; //rkdalfks

private:
    bool toggleButton1State;
    bool toggleButton2State;

    int slider1Value; //test

    touchgfx::Callback<Model, bool> toggleButton1StateChangedCallback;
    touchgfx::Callback<Model, bool> toggleButton2StateChangedCallback;
};

#endif /* MODEL_HPP */
