import Sonora.Engine.Platform.Window;
import std;
int main() {
  std::cout << "Hello, Sonora Engine!" << std::endl;
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  sonora::engine::platform::WindowSize windowSize{.width = 800, .height = 600};
  return 0;
}