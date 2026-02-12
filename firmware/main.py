import board
from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.modules.encoder import EncoderHandler
from kmk.extensions.rgb import RGB
from kmk.modules.macros import Press, Release, Tap, Macros

# Initialize
keyboard = KMKKeyboard()

keyboard.diode_orientation = None

keyboard.modules.append(Macros())

# direct pin to switches, no matrix
keyboard.direct_pins = [
    board.D3,
    board.D2,
    board.D1,
    board.D0,
    board.D4,
    board.D5,
    board.D6
]

# Knob
encoder_handler = EncoderHandler()
encoder_handler.pins = (
    (board.D8, board.D9, board.D10, False),
)
# Knob click toggles between layers
encoder_handler.map = [
    ((KC.MEDIA_VOLUME_UP, KC.MEDIA_VOLUME_DOWN, KC.TG(1)),),
    ((KC.MEDIA_VOLUME_UP, KC.MEDIA_VOLUME_DOWN, KC.TG(1)),),
]

keyboard.modules.append(encoder_handler)

# LEDs
rgb = RGB(
    pixel_pin=board.D7,
    num_pixels=16,
    rgb_order='GRB',
    animation_mode=RGB.RAINBOW
)
keyboard.extensions.append(rgb)

# ex. of macro: KC.MACRO(Press(KC.LCTRL), Tap(KC.C), Release(KC.LCTRL))

# Keymap
keyboard.keymap = [
    # Layer 0:
    [
        KC.Q, 
        KC.W, 
        KC.E, 
        KC.R, 
        KC.T, 
        KC.Y, 
        KC.U
    ],
    
    # Layer 1:
    [
        KC.PSCREEN, # screenshot
        KC.MACRO(Press(KC.LALT), Tap(KC.F9), Release(KC.LALT)), # record toggle
        KC.MACRO(Press(KC.LALT), Press(KC.LSHIFT), Tap(KC.F10), Release(KC.LSHIFT), Release(KC.LALT)), # instant replay
        KC.Q, 
        KC.W, 
        KC.E, 
        KC.LWIN(KC.L) # lock screen
    ],
]

if __name__ == '__main__':
    keyboard.go()