'''
CROSS FIELD.py
==============
Created: 14.08.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
This is an example input script for PaTriC that simulates the cross field drift of a positron.
'''

from deck_helper import *

createControl(2e-8, 180, HIGUERA_CARY, 18)
createParticles(1, 1, 1, (Static(7.5183, 4.3407, 0), ), (Static(0.6e8, -1.03923e8, 1.414e8), ))
createFields((Static(100, 0, 0), ), (Static(0, 0, 1e-4), ))
createOutput('cross_field', 'test', None, False, (POS_X, POS_Y, POS_Z))