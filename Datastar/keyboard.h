/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Keyboard input processor.
/// Function prefix: kb_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "window_manager.h"
#include "logger.h"

sfBool kb_IsEnabled();

/// Enables keyboard input.
void kb_Enable();

/// Disables keyboard input.
void kb_Disable();

/// Checks if a keyboard key is currently idle.
sfBool kb_TestIdle(sfKeyCode _k);

/// Checks if a keyboard key was just pressed.
sfBool kb_TestPress(sfKeyCode _k);

/// Checks if a keyboard key is being held down.
sfBool kb_TestHold(sfKeyCode _k);

/// Checks if a keyboard key was just released.
sfBool kb_TestRelease(sfKeyCode _k);

/// Checks if a key was just pressed.
sfBool kb_TestPressAnyKey();

/// Monitors the current state of the keyboard. Note that if the game window doesn't currently have focus, then no input will be recorded at all.
void kb_Update();