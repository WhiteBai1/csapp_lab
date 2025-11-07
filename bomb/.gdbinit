# 设置默认文件输入
set args psol.txt
set debuginfod enabled on

# 设置各个phase的断点
# b phase_1
# b phase_2
b phase_3
b phase_4
b phase_5
b phase_6

# 跳过炸弹
b explode_bomb