#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model()
	: modelListener(0),
	  toggleButton1State(true), //test
	  toggleButton2State(true),
	  slider1Value(50)
{
}

void Model::tick()
{
	tickCounter++;
	if(tickCounter % 60 == 0)
	{
		if(modelListener){
			modelListener->updateClock();
		}
	}
}

void Model::setToggleButton1State(bool state)
{
    if (toggleButton1State != state)
    {
        toggleButton1State = state;
        if (toggleButton1StateChangedCallback.isValid())
        {
            toggleButton1StateChangedCallback.execute(toggleButton1State);
        }
    }
}

void Model::setToggleButton2State(bool state)
{
    if (toggleButton2State != state)
    {
        toggleButton2State = state;
        if (toggleButton2StateChangedCallback.isValid())
        {
            toggleButton2StateChangedCallback.execute(toggleButton2State);
        }
    }
}

bool Model::getToggleButton1State() const
{
    return toggleButton1State;
}

bool Model::getToggleButton2State() const
{
    return toggleButton2State;
}

void Model::setSlider1Value(int value) //test
{
	slider1Value = value;
}

int Model::getSlider1Value() const //test
{
	return slider1Value;
}
