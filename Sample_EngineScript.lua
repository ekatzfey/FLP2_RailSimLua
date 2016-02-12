--these variables are just used to stop the messages Ive made spamming the screen endlessly while a button is held
HornMessageDisplayed = false
JMessageDisplayed = false

--This stores the keyboard press library function
presskey = nil


function Initialise ()
    Call("BeginUpdate")

	-- Load the keypress library
	presskey = loadlib("C:\\Temp\\CDLL.dll", "init")
end

function OnControlValueChange ( name, index, value )

	if Call( "*:ControlExists", name, index ) then

		Call( "*:SetControlValue", name, index, value );

	end

end


function Update (time)
    --this is the button in the cab you press with the mouse
    --When the script detects it is fully pressed
    if Call("GetControlValue", "Horn" ,0) == 1 then
        --a message will pop up if the message hasnt been displayed yet
        if HornMessageDisplayed == false then
            --show a message
			if presskey ~= nil then
				SysCall ( "ScenarioManager:ShowAlertMessageExt", "Function is valid ", "Horn" ,2, 0)
			else
				SysCall ( "ScenarioManager:ShowAlertMessageExt", "Function is nil ", "Horn" ,2, 0)
			end
            --and stop any more being displayed
            HornMessageDisplayed = true

			-- Press the 4 key which switches the view
			presskey(52, 0)

			-- Press shift - z which starts FPS viewer
			presskey(90, 1)

			-- Press ctrl - q which puts up quit screen
			presskey(81, 2)

        end
        --This is the point the dll should  sent a keypress to the sim (In this example use j)
    else
        --Key released allow the next mesage to display
        HornMessageDisplayed = false
    end

    --for the purposes of testing I have set another invisible button mapped to j so you can see a positive result
    if Call("GetControlValue", "TestValue" ,0) == 1 then
        --if the message hant been displayed yet
        if JMessageDisplayed == false then
            --show a message
            SysCall ( "ScenarioManager:ShowAlertMessageExt", "Debug Msg", "J keypress" ,2, 0)
            --and stop any more being displayed
            JMessageDisplayed = true
        end
    else
        --until the key is released
        JMessageDisplayed = false
    end

    --so You're pressing the horn in that cab, thats pressing j through the dll which is then activating TestValue


end
