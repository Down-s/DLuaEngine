local BALL = {
    x = 0,
    y = 0,
    radius = 32,
}
BALL.__index = BALL

function BALL:SetPos(x, y)
    self.x = x
    self.y = y
end

function BALL:SetRadius(r)
    self.radius = r
end

function BALL:SetColor(r, g, b)
    self.r = r
    self.g = g
    self.b = b
end

function BALL:Render()
    for i = 1, 360 do
        window.SetDrawColor(self.r, self.g, self.b)
        window.DrawLine(self.x, self.y, (self.x + (math.sin(i) * self.radius)), (self.y + math.cos(i) * self.radius))
    end
end

function BALL:PhysicsUpdate(tBalls)
    for i, ball in ipairs(tBalls) do
        if (ball ~= self and self:IsColliding(ball)) then
            local Distance = math.sqrt((self.x - ball.x)*(self.x - ball.x) + (self.y - ball.y)*(self.y - ball.y))
            local Overlap = (Distance - self.radius - ball.radius) * 0.5

            self.x = self.x - (Overlap * (self.x - ball.x) / Distance)
            self.y = self.y - (Overlap * (self.y - ball.y) / Distance)

            ball.x = ball.x + (Overlap * (self.x - ball.x) / Distance)
            ball.y = ball.y + (Overlap * (self.y - ball.y) / Distance)
        end
    end
end

function BALL:IsColliding(other)
    local Distance = (self.x - other.x)^2 + (self.y - other.y)^2
    local SqRadius = (self.radius + other.radius) * (self.radius + other.radius)

    return Distance <= SqRadius
end

function Create()
    return setmetatable({
        ball = {}
    }, BALL)
end

return {Create = Create}