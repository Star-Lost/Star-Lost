# This script generates the indices for the wall model into the roguelike spritesheet
# While its use is limited to walls, it can be used as an example for creating
# similar scripts for other models.

frames = [(221, 204, 'sand'), (340, 204, 'stone'), (459, 204, 'metal'), (579, 204, 'wood')];

tiles = [
    ('0100', 0, 0, 'right'),
    ('0101', 0, 1, 'horizontal'),
    ('0001', 0, 2, 'left'),
    ('0110', 0, 3, 'top left corner'),
    ('0011', 0, 4, 'top right corner'),
    ('1110', 0, 5, 't-section right'),
    ('1101', 0, 6, 't-section up'),
    
    ('0010', 1, 0, 'down'),
    ('1111', 1, 1, 'cross'),
    ('1010', 1, 2, 'vertical'),
    ('1100', 1, 3, 'bottom left corner'),
    ('1001', 1, 4, 'bottom right corner'),
    ('1011', 1, 5, 't-section left'),
    ('0111', 1, 6, 't-section down'),

    ('1000', 2, 0, 'up')
]


file = open('output.txt', 'w');
for tile in tiles:
    file.write('model::named_animation{{ // {}\n'.format(tile[3]));
    file.write('\tstd::string{{ "{}" }},\n'.format(tile[0]));
    file.write('\tanimation{\n');
    for frame in frames:
        file.write('\t\tframe{{ sf::IntRect{{{}, {}, 16, 16}} }}{} // {}\n'.format(frame[0] + tile[2] * 17, frame[1] + tile[1] * 17, ' ' if frame == frames[3] else ',', frame[2]));
    file.write('\t}\n');
    file.write('},\n\n');
file.close();
