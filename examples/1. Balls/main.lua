balls = require("ball")

local tBalls = {}
local BallCount = 5

local function NewBall()
    local scrw, scrh = window.GetSize()

    local ball = balls.Create()
    ball:SetPos(math.random(0, scrw), math.random(0, scrh))
    ball:SetRadius(math.random(32, 64))
    ball:SetColor(math.random(0, 255), math.random(0, 255), math.random(0, 255))

    tBalls[#tBalls + 1] = ball
end

function DE.Init()
    window.SetBackgroundColor(20, 20, 20)
    window.SetTitle("Balls Example")
    window.SetSize(600, 400)

    for i = 1, BallCount do
        NewBall()
    end
end

function DE.Render()
    
    for i, ball in ipairs(tBalls) do
        if (i == 1) then
            local mx, my = window.GetMousePos()
            ball:SetPos(mx, my)
        end

        ball:Render()
        ball:PhysicsUpdate(tBalls)
    end
end

function DE.KeyDown(c)
end

function DE.KeyUp(c)
end

function DE.MouseDown(m)
    if (m == 1) then
        NewBall()
    end

    if (m == 2) then
        tBalls[#tBalls] = nil
    end
end

function DE.MouseUp(m)
end