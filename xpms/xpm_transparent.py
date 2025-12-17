# xpm_transparent.py
from PIL import Image

def convert_to_xpm_transparent(input_img_path, output_xpm_path, threshold=240):
    """
    将图片中接近白色的部分替换为透明，并生成 XPM 文件
    threshold: 0-255, RGB 大于该值认为是白色
    """
    img = Image.open(input_img_path).convert("RGBA")
    width, height = img.size
    pixels = img.load()

    # 建立颜色表
    color_table = {}
    chars = []
    next_char = 0

    def get_char_for_color(color):
        nonlocal next_char
        if color in color_table:
            return color_table[color]
        if next_char < 94:
            c = chr(33 + next_char)  # 可打印 ASCII
        else:
            c = chr(33 + (next_char // 94)) + chr(33 + (next_char % 94))
        color_table[color] = c
        next_char += 1
        return c

    # 替换接近白色为透明
    for y in range(height):
        for x in range(width):
            r, g, b, a = pixels[x, y]
            if r >= threshold and g >= threshold and b >= threshold:
                pixels[x, y] = (0, 0, 0, 0)  # 透明

    # 生成颜色表
    xpm_colors = {}
    for y in range(height):
        for x in range(width):
            rgba = pixels[x, y]
            if rgba[3] == 0:
                color = "None"
            else:
                color = '#{:02X}{:02X}{:02X}'.format(rgba[0], rgba[1], rgba[2])
            xpm_colors[rgba] = color

    # 写 XPM 文件
    with open(output_xpm_path, 'w') as f:
        f.write("/* XPM */\n")
        f.write("static char * door_open[] = {\n")
        f.write(f'"{width} {height} {len(xpm_colors)} 1",\n')

        # 写颜色表
        color_index = {}
        idx = 0
        for rgba, color in xpm_colors.items():
            c = chr(33 + idx)
            color_index[rgba] = c
            idx += 1
            f.write(f'"{c} c {color}",\n')

        # 写像素数据
        for y in range(height):
            line = '"'
            for x in range(width):
                line += color_index[pixels[x, y]]
            line += '"'
            if y < height - 1:
                line += ','
            line += '\n'
            f.write(line)

        f.write("};\n")

if __name__ == "__main__":
    # 调用示例
    convert_to_xpm_transparent("door_open.png", "door_open_transparent.xpm")
