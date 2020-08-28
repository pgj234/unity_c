#%%
from PIL import Image, ImageDraw
from xml.etree.ElementTree import parse
from IPython.display import display

print(f'module load ok')

#%%
ori_img = Image.open('../res/tanks/sheet_tanks.png')

tree = parse('../res/tanks/sheet_tanks.xml')
rootNode = tree.getroot()
_nodes = rootNode.findall('SubTexture')

for v in _nodes :
    _name = v.attrib['name']
    _x = int(v.attrib['x'])
    _y = int(v.attrib['y'])
    width = int(v.attrib['width'])
    height = int(v.attrib['height'])
    print(f"\n{_name:32}, {_x:3}, {_y:3}, {width:3}, {height:3}")
    crop_img = ori_img.crop((_x, _y, width + _x, height + _y))
    display(crop_img)
    #crop_img.save(f'{_name}')
    
# %%
