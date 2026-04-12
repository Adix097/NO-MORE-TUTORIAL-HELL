#include <raylib.h>

class Ball {
    private:
        float x, y;
        int radius;
        float speed_x, speed_y;
        Color color;

    public:
        Ball(float x, float y, int r, float sx, float sy, Color c = WHITE) : x(x), y(y), radius(r), speed_x(sx), speed_y(sy), color(c) {}

        Vector2 getCenter() const { return {x, y}; }
        Vector2 getSpeed() const { return {speed_x, speed_y}; }
        int getRadius() const { return radius; }

        void setX(float newX) { x = newX; }

        void draw() {
            DrawCircle(x, y, radius, color);
        }

        void update() {
            x += speed_x;
            y += speed_y;

            // vertical bounce only
            if (y + radius >= GetScreenHeight() || y - radius <= 0) speed_y *= -1;
        }

        void reverseX() {
            speed_x *= -1;
        }
};

class Paddle {
    protected:
        float x, y;
        float width, height;
        int speed;
        Color color;

    public:
        Paddle(float x, float y, float w, float h, int s, Color c = WHITE) : x(x), y(y), width(w), height(h), speed(s), color(c) {}

        Rectangle getRect() const {
            return {x, y, width, height};
        }

        void draw() {
            DrawRectangle(x, y, width, height, color);
        }

        void move_up() {
            if (y > 0) y -= speed;
        }

        void move_down() {
            if (y + height < GetScreenHeight()) y += speed;
        }
};

class CpuPaddle : public Paddle {
    public:
        using Paddle::Paddle;

        void update(float ball_y, float ball_vx) {
            if (ball_vx <= 0) return;

            float center = y + height / 2;
            float threshold = 10;

            if (center > ball_y + threshold) move_up();
            else if (center < ball_y - threshold) move_down();
        }
};

int main() {
    const int width = 1280;
    const int height = 800;

    InitWindow(width, height, "pong");
    SetTargetFPS(120);

    Ball ball(width/2, height/2, 20, 5, 5);
    Paddle player(10, height/2 - 60, 25, 120, 3);
    CpuPaddle cpu(width - 35, height/2 - 60, 25, 120, 3);

    int player_score = 0;
    int cpu_score = 0;

    bool canScore = true;

    enum GameState { PLAYING, GAME_OVER };
    GameState state = PLAYING;

    int winner = 0;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        if (state == PLAYING) {
            if (IsKeyDown(KEY_W)) player.move_up();
            if (IsKeyDown(KEY_S)) player.move_down();

            ball.update();
            Vector2 pos = ball.getCenter();
            Vector2 vel = ball.getSpeed();

            cpu.update(pos.y, vel.x);

            // paddle collision
            Rectangle pRect = player.getRect();
            if (CheckCollisionCircleRec(pos, ball.getRadius(), pRect)) {
                ball.reverseX();
                ball.setX(pRect.x + pRect.width + ball.getRadius());
            }

            Rectangle cRect = cpu.getRect();
            if (CheckCollisionCircleRec(pos, ball.getRadius(), cRect)) {
                ball.reverseX();
                ball.setX(cRect.x - ball.getRadius());
            }

            // scoring
            if (pos.x - ball.getRadius() <= 0) {
                if (canScore) {
                    cpu_score++;
                    canScore = false;
                }
                ball.reverseX();
            }

            if (pos.x + ball.getRadius() >= width) {
                if (canScore) {
                    player_score++;
                    canScore = false;
                }
                ball.reverseX();
            }

            // reset scoring lock
            if (pos.x > width/4 && pos.x < 3*width/4) {
                canScore = true;
            }

            // win condition
            if (player_score == 10) {
                state = GAME_OVER;
                winner = 1;
            }
            if (cpu_score == 10) {
                state = GAME_OVER;
                winner = 0;
            }

            player.draw();
            cpu.draw();
            ball.draw();

            DrawText(TextFormat("%i", cpu_score), width/4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), 3*width/4 - 20, 20, 80, WHITE);
        }
        else {
            const char* text = (winner == 1) ? "Player Won!" : "CPU Won!";
            int fontSize = 100;
            int textWidth = MeasureText(text, fontSize);

            DrawText(text,
                     width/2 - textWidth/2,
                     height/2 - fontSize/2,
                     fontSize,
                     (winner == 1) ? GREEN : RED);

            DrawText("Press R to Restart",
                     width/2 - 150,
                     height/2 + 60,
                     20,
                     GRAY);

            if (IsKeyPressed(KEY_R)) {
                player_score = 0;
                cpu_score = 0;
                state = PLAYING;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
