local Iters = 35

local Mandelbrot = {}
function GenerateMandelbrot()
    local scrw, scrh = window.GetSize()

    for x = 1, scrh do
        for y = 1, scrh do
            -- Remap these from -2 to 2
            local a = (x / scrh) * 4 - 2
            local b = (y / scrh) * 4 - 2

            local ca = a
            local cb = b

            local n = 0

            while (n < Iters) do
                local aa = a*a - b*b
                local bb = 2 * a * b

                a = aa + ca
                b = bb + cb

                if (a + b > 128) then break end

                n = n + 1
            end
            
            local alpha = n / 100 * 255
            if (n == Iters) then
                alpha = 0
            end
            
            Mandelbrot[x] = Mandelbrot[x] or {}
            Mandelbrot[x][y] = alpha
        end
    end

    print("Mandelbrot Generated!")
end

function DE.Init()
    window.SetBackgroundColor(20, 20, 20)
    window.SetTitle("Mandelbrot Example")
    window.SetSize(450, 450)

    GenerateMandelbrot()
end

function DE.Render()
    local scrw, scrh = window.GetSize()

    for x = 1, scrw do
        for y = 1, scrh do
            local alpha = Mandelbrot[x][y]
            window.SetDrawColor(alpha, alpha, alpha, 255)
            window.DrawPixel(x, y)
        end
    end
end

function DE.KeyDown(c)
end

function DE.KeyUp(c)
end

local function clamp(v, min, max)
    return math.min(math.max(v, min), max)
end

function DE.MouseDown(m)
    if (m == 1) then
        Iters = clamp(Iters + 5, 5, 250)
        GenerateMandelbrot()
    end

    if (m == 2) then
        Iters = clamp(Iters - 5, 5, 250)
        GenerateMandelbrot()
    end
end

function DE.MouseUp(m)
end