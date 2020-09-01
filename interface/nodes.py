# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sorting.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 00:34:52 by ciglesia          #+#    #+#              #
#    Updated: 2020/08/17 17:28:47 by ciglesia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from tkinter import *
import sys
import os
import subprocess
import time

CONTINUE = 0
SPEED = 0.075
POS = 0
commands = []
pb = []
pa = []
invcmd = []
w1 = 0
w2 = 0

def center(toplevel):
    toplevel.update_idletasks()

    screen_width = toplevel.winfo_screenwidth()
    screen_height = toplevel.winfo_screenheight()

    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = screen_width/2 - size[0]/2
    y = screen_height/2 - size[1]/2

    toplevel.geometry("+%d+%d" % (x, y))
    toplevel.title("Sorting!")

def fill_pile(nodes, w, xdif, ydif):
    circle = {}
    if (xdif <= 0):
        xdif = 1
    if (ydif <= 0):
        ydif = 1
    n = 900/xdif
    m = 600/ydif
    for node in nodes:
        x = nodes[node][0]
        y = nodes[node][1]
        circle[node] = w.create_oval(n*x, m*y, n*x + 20, m*y + 20, fill="tomato", outline="black")
    return (circle)

def swap(p, w):
    x0, y0, x1, y1 = w.coords(p[0])
    x00, y00, x01, y01 = w.coords(p[1])
    w.coords(p[0], x0, y00, x1, y01)
    w.coords(p[1], x00, y0, x01, y1)
    p[0], p[1] = p[1], p[0]

def rotate(p, w):
    for i in range(len(p) - 1):
        x0, y0, x1, y1 = w.coords(p[i])
        x00, y00, x01, y01 = w.coords(p[i+1])
        w.coords(p[i], x0, y00, x1, y01)
        w.coords(p[i+1], x00, y0, x01, y1)
        p[i], p[i+1] = p[i+1], p[i]

def revrot(p, w):
    for i in range(len(p) - 1, 0, -1):
        x0, y0, x1, y1 = w.coords(p[i])
        x00, y00, x01, y01 = w.coords(p[i-1])
        w.coords(p[i], x0, y00, x1, y01)
        w.coords(p[i-1], x00, y0, x01, y1)
        p[i], p[i-1] = p[i-1], p[i]

def pas(p1, p2, w1, w2):
    x0, y0, x1, y1 = w1.coords(p1[0])
    rotate(p1, w1)
    color = w1.itemcget(p1[-1], "fill")
    diff = abs(y1 - y0)
    w1.delete(p1[-1])
    p1.pop()
    p2.insert(0, w2.create_rectangle(x0, y0, x1, y1, fill=color, outline=color))
    for i in range(1,len(p2)):
        x0, y0, x1, y1 = w2.coords(p2[i-1])
        x00, y00, x01, y01 = w2.coords(p2[i])
        w2.coords(p2[i], x00, y0+diff, x01, y1+diff)

def invert(cmd):
    global invcmd
    cm = {'sa':"sa", 'sb':"sb", 'ss':"ss", 'ra':"rra", 'rb':"rrb", 'rr':"rrr", 'rra':"ra", 'rrb':"rb", 'rrr':"rr", 'pa':"pb", 'pb':"pa"}
    for c in cmd:
        invcmd.append(cm[c])
    return invcmd

def exec_cmd(c, pa, pb, w1, w2):
    if c == 'sa' and len(pa) >= 2:
        swap(pa, w2)
    if c == 'sb' and len(pb) >= 2:
        swap(pb, w1)
    if c == 'ss':
        if len(pa) >= 2:
            swap(pa, w2)
        if len(pb) >= 2:
            swap(pb, w1)
    if c == 'ra' and len(pa) >= 2:
        rotate(pa, w2)
    if c == 'rb' and len(pb) >= 2:
        rotate(pb, w1)
    if c == 'rr':
        if len(pa) >= 2:
            rotate(pa, w2)
        if len(pb) >= 2:
            rotate(pb, w1)
    if c == 'rra' and len(pa) >= 2:
        revrot(pa, w2)
    if c == 'rrb' and len(pb) >= 2:
        revrot(pb, w1)
    if c == 'rrr':
        if len(pa) >= 2:
            rotate(pa[::-1], w2)
        if len(pb) >= 2:
            rotate(pb[::-1], w1)
    if c == 'pa' and len(pb) >= 1:
        pas(pb, pa, w1, w2)
    if c == 'pb' and len(pa) >= 1:
        pas(pa, pb, w2, w1)

def exec_ps(cmds, w1, w2, w3):
    global CONTINUE
    global SPEED
    global POS
    global commands
    global pb
    global pa

    cm = {b'sa':"sa", b'sb':"sb", b'ss':"ss", b'ra':"ra", b'rb':"rb", b'rr':"rr", b'rra':"rra", b'rrb':"rrb", b'rrr':"rrr", b'pa':"pa", b'pb':"pb"}
    for cmd in cmds:
        try:
            commands.append(cm[cmd])
            w3.insert(END, cm[cmd])
        except: print(str(cmd)[2:-1])
    w3.insert(END, "")
    w3.insert(END, " # of cmds:" + str(len(commands)))
    invcmd = invert(commands)
    # right and left arrow: cmd and cmd^-1 lists with same index
    while POS < len(commands):
        while CONTINUE == 0:
            try:
                w2.update()
                w1.update()
            except: exit()
            time.sleep(0.1)   # Sleep 0.1
        if POS < len(commands):
            exec_cmd(commands[POS], pa, pb, w1, w2)
            POS += 1
        time.sleep(SPEED)
        sys.stdout.flush()
        w3.yview_scroll(1, 'units')
        try:
            w2.update()
            w1.update()
        except: exit()

def globalv(event):
    global CONTINUE
    CONTINUE = (CONTINUE + 1) % 2

def speedup(event):
    global SPEED
    if SPEED > 0.0001:
        SPEED /= 2

def speedwn(event):
    global SPEED
    if SPEED < 5:
        SPEED *= 2

def prevcmd(event):
    global CONTINUE
    global POS
    global pa
    global pb
    global invcmd
    global w1
    global w2
    global w3

    if CONTINUE == 0 and POS > 0:
        exec_cmd(invcmd[POS-1], pa, pb, w1, w2)
        w3.yview_scroll(-1, 'units')
        POS -= 1

def nextcmd(event):
    global CONTINUE
    global POS
    global pa
    global pb
    global commands
    global w1
    global w2
    global w3

    if CONTINUE == 0 and POS < len(commands):
        exec_cmd(commands[POS], pa, pb, w1, w2)
        w3.yview_scroll(1, 'units')
        POS += 1

if __name__ == '__main__':
    win = Tk()
    win.geometry('1000x850')
    center(win)
    w1 = Canvas(win, width=1000, height=700, background="gray10")
    w3 = Listbox(win, width=8, height=4, background="black", foreground="white", font=("monospace", 12))
    w3.pack(side="bottom", fill=BOTH, expand=1)
    w1.pack()

    nodes = {}
    xmin = 0
    xmax = 0
    ymin = 0
    ymax = 0
    for line in sys.stdin:
        s = line.split()
        if (line[0] != 'L' and len(s) == 3):
            try:
                nodes[s[0]] = list(map(lambda x: int(x), s[1:]))
                if (xmin > int(s[1])):
                    xmin = int(s[1])
                if (xmax < int(s[1])):
                    xmax = int(s[1])
                if (ymin > int(s[2])):
                    ymin = int(s[2])
                if (ymax < int(s[2])):
                    ymax = int(s[2])
                #print(nodes[s[0]], end="")
            except: pass
    print("")
    fill_pile(nodes, w1, abs(xmin - xmax), abs(ymin - ymax))
    '''
    win.bind("<space>", globalv)
    win.bind("<Up>", speedup)
    win.bind("<Down>", speedwn)
    win.bind("<Left>", prevcmd) # prev
    win.bind("<Right>", nextcmd) # next
    exec_ps(cmds, w1, w2, w3)#################
    '''
    win.mainloop()
