f = open('input4.txt')

image = []
for line in f:
    m = line.strip()
    image.append(m)
    
print image
temp = ''
for i in range(len(image)):
    for j in range(len(image[i])):
        if i < len(image) -1 and j < len(image[i]) -1:
            if image[i+1][j] == 'X' or image[i-1][j] == 'X' or image[i][j+1] == 'X' or image[i][j-1] == 'X':
                image[i][j] = 'X'
                temp += image[i][j]

print temp

