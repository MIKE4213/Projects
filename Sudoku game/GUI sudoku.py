import pygame
from sys import exit
pygame.init()
from Sudoku_game_solver import check, solvesudoku, pickempty

screen=pygame.display.set_mode((500, 700))
pygame.display.set_caption("Sudoku game")

# Start Sudoku Board.
grid = [
 [0, 5, 0, 0, 0, 0, 0, 6, 0],
 [0, 0, 0, 0, 0, 0, 0, 0, 1],
 [2, 0, 0, 6, 0, 7, 0, 0, 3],
 [9, 6, 0, 0, 4, 8, 0, 5, 2],
 [4, 0, 0, 0, 0, 0, 0, 0, 0],
 [0, 8, 0, 1, 0, 0, 0, 0, 0],
 [5, 9, 0, 7, 0, 2, 0, 1, 6],
 [0, 4, 0, 0, 0, 6, 0, 0, 0],
 [0, 0, 8, 0, 0, 0, 0, 0, 0]
]

x = 0
y = 0
dif = 500 / 9
val = 0


def get_cord(pos):
    global x
    x = pos[0]//dif
    global y
    y = pos[1]//dif

def draw_box():
    for i in range(2):
        pygame.draw.line(screen, (255, 0, 0), (x * dif-3, (y + i)*dif), (x * dif + dif + 3, (y + i)*dif), 7)
        pygame.draw.line(screen, (255, 0, 0), ((x + i)* dif, y * dif), ((x + i) * dif, y * dif + dif), 7)


font1 = pygame.font.SysFont("Pacifico", 70)

def draw():
    # Draw the lines
    for i in range (9):
        for j in range (9):
            if grid[i][j]!= 0:
                pygame.draw.rect(screen, ('Gray'), (i * dif, j * dif, dif + 1, dif + 1))
 
                # Fill grid numbers
                text1 = font1.render(str(grid[i][j]), 1, ('Red'))
                screen.blit(text1, (i * dif + 15, j * dif + 5))
    # Draw lines horizontally and vertically to form grid
    for i in range(10):
        if i % 3 == 0 :
            thick = 7
        else:
            thick = 1
        pygame.draw.line(screen, (0, 0, 0), (0, i * dif), (500, i * dif), thick)
        pygame.draw.line(screen, (0, 0, 0), (i * dif, 0), (i * dif, 500), thick)
 
def draw_val(val):
    text1 = font1.render(str(val), 1, (0, 0, 0))
    screen.blit(text1, (x * dif + 15, y * dif + 1))


#test_image=pygame.image.load('Chap04/wall.jpeg')
#test_font=pygame.font.Font(None,50)
#text_surf = test_font.render('Sudoku game', False , 'Black')

font2 = pygame.font.SysFont("Pacifico", 40)

def instruction():
    text1 = font2.render("R-RESTART ---- E-Blank", 1, (0, 0, 0))
    text2 = font2.render("S-Solution", 1, (0, 0, 0))
    text3 = font2.render("Solve the Sudoku and have fun", 1, (0, 0, 0))
    screen.blit(text1, (10, 520))
    screen.blit(text2, (10, 560))
    screen.blit(text3, (10, 600))
 

def result():
    text1 = font2.render("Congrats, you finished!", 1, (0, 0, 0))
    screen.blit(text1, (20, 640))
run = True
flag1 = 0

#while True:
    #for event in pygame.event.get():
    #    if event.type == pygame.QUIT:
    #     pygame.quit()
     #    exit()
    
    #screen.fill((202,228,241))
    #screen.blit(text_surf,(0,0))
    #draw our elements
    #update all
    #pygame.display.update()
    #clock.tick(60)

while run:
     
    #background
    screen.fill((255, 255, 255))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False 
        # mouse position
        if event.type == pygame.MOUSEBUTTONDOWN:
            flag1 = 1
            pos = pygame.mouse.get_pos()
            get_cord(pos)
        # key events
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                x-= 1
                flag1 = 1
            if event.key == pygame.K_RIGHT:
                x+= 1
                flag1 = 1
            if event.key == pygame.K_UP:
                y-= 1
                flag1 = 1
            if event.key == pygame.K_DOWN:
                y+= 1
                flag1 = 1   
            if event.key == pygame.K_1:
                val = 1
            if event.key == pygame.K_2:
                val = 2   
            if event.key == pygame.K_3:
                val = 3
            if event.key == pygame.K_4:
                val = 4
            if event.key == pygame.K_5:
                val = 5
            if event.key == pygame.K_6:
                val = 6
            if event.key == pygame.K_7:
                val = 7
            if event.key == pygame.K_8:
                val = 8
            if event.key == pygame.K_9:
                val = 9 
            if event.key == pygame.K_RETURN:
                flag2 = 1  
            # If E pressed clear the sudoku board
            if event.key == pygame.K_e:
                grid =[
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0]
                ]
            # If R is pressed reset the board to default
            if event.key == pygame.K_r:
                grid = [
                          [0, 5, 0, 0, 0, 0, 0, 6, 0],
                          [0, 0, 0, 0, 0, 0, 0, 0, 1],
                          [2, 0, 0, 6, 0, 7, 0, 0, 3],
                          [9, 6, 0, 0, 4, 8, 0, 5, 2],
                          [4, 0, 0, 0, 0, 0, 0, 0, 0],
                          [0, 8, 0, 1, 0, 0, 0, 0, 0],
                          [5, 9, 0, 7, 0, 2, 0, 1, 6],
                          [0, 4, 0, 0, 0, 6, 0, 0, 0],
                          [0, 0, 8, 0, 0, 0, 0, 0, 0]
                      ]
            # If S is pressed solve the sudoku
            if event.key == pygame.K_s:
                solvesudoku(grid)
    if val != 0:           
        draw_val(val)
        if check(grid, int(x), int(y), val) == True:
            grid[int(x)][int(y)] = val
            flag1 = 0
        else:
            grid[int(x)][int(y)] = 0
        val = 0
    if pickempty(grid) == False:
        result()       
    draw() 
    if flag1 == 1:
        draw_box()      
    instruction()   
 
    # Update
    pygame.display.update() 
 
# Quit game
pygame.quit()