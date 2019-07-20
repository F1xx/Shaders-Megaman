#include "GamePCH.h"

#include "GameObjects/PlayerController.h"

void PlayerController::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == EventType_Input )
    {
#if WIN32
        InputEvent* pInput = (InputEvent*)pEvent;

        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard )
        {
            int keyID = pInput->GetID();

            if( pInput->GetInputState() == InputState_Pressed )
            {
                if( keyID == VK_UP    || keyID == 'W' ) { m_Directions |= DIR_UP; }
                if( keyID == VK_DOWN  || keyID == 'S' ) { m_Directions |= DIR_DOWN; }
                if( keyID == VK_LEFT  || keyID == 'A' ) { m_Directions |= DIR_LEFT; }
                if( keyID == VK_RIGHT || keyID == 'D' ) { m_Directions |= DIR_RIGHT; }
                if( keyID == 'Q' ) { m_Directions |= DIR_OUT; }
                if( keyID == 'E' ) { m_Directions |= DIR_IN; }
            }

            if( pInput->GetInputState() == InputState_Released )
            {
                if( keyID == VK_UP    || keyID == 'W' ) { m_Directions &= ~DIR_UP; }
                if( keyID == VK_DOWN  || keyID == 'S' ) { m_Directions &= ~DIR_DOWN; }
                if( keyID == VK_LEFT  || keyID == 'A' ) { m_Directions &= ~DIR_LEFT; }
                if( keyID == VK_RIGHT || keyID == 'D' ) { m_Directions &= ~DIR_RIGHT; }
				if (keyID == 'Q') { m_Directions &= ~DIR_OUT; }
				if (keyID == 'E') { m_Directions &= ~DIR_IN; }
            }
        }
#endif
    }
}
