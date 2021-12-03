#include <bangtal>
using namespace bangtal;


int main()
{
	//1. 장면을 생성
	auto scene1 = Scene::create("룸1", "Images/방1.jpg"); //auto = scene 넘겨주기용 포인터,뒤의 값에 따라 자동으로 타입 결정
	auto scene2 = Scene::create("룸2", "Images/방2.jpg");
	auto scene3 = Scene::create("???", "Images/방3.png");
	showMessage("눈을 떠보니 이상한 병실에 갇혀있다. 단서를 모아 밖으로 탈출하자.");


	//2. 노래 재생
	auto bgm1 = createSound("Bgm/bgm.mp3");
	auto loop = true;
	playSound(bgm1, loop = true);


	//3. 단서 1 - 열쇠 생성

	auto key = Object::create("Images/열쇠.png", scene1, 400, 325);
	key->setScale(0.1f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		key->pick();

		return true;
		});

	//4. 단서 2 - 시계 생성

	auto watch = Object::create("Images/시계.png", scene1, 600, 550);
	watch->setScale(0.2f);

	//5. 비밀문 + 패스워드 + 잠금/해제
	auto open1 = false;// = bool
	auto secret_door = Object::create("Images/스위치.png", scene1, 1180, 450);
	auto locked1 = true;

	secret_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {


		if (locked1) {
			showMessage("아무래도 이게 뭔가의 스위치인것 같네. 위에 있는 키패드에 뭔가를 입력하면 되려나?\n아, 그러고보니 열쇠를 베개맡에 둔 기억이 나.");


		}
		else if (open1 && key->isHanded()) {
			scene2->enter();
			showMessage("윽... 방이 너무 어둡다. 어디 스위치 같은 건 없으려나?");
			return true;

		}


		return true;
		});



	secret_door->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked1 = false;
		showMessage("...! 열렸다!");
		open1 = true;
		return true;
		});


	auto keypad = Object::create("Images/키패드.png", scene1, 1180, 500);

	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			showKeypad("KEY1010", secret_door);

			return true;


		});

	//씬 1 끝.
	//씬 2 시작

	auto scene2_light_switch = Object::create("Images/스위치.png", scene2, 830, 400);
	scene2->setLight(0.1f);

	auto scene2_door = Object::create("Images/닫힌-문.png", scene2, 450, 190);
	auto scene2_light_check = false;
	auto scene2_password = Object::create("Images/힌트.png", scene2, 100, 100, false);
	auto scene2_keypad = Object::create("Images/키패드.png", scene2, 350, 400);

	auto scene2_locked = true;
	auto scene2_open = false;

	scene2_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (scene2_locked) {
			showMessage("문이 잠겨있다.");
		}

		else if (scene2_open = true) {
			scene3->enter();
			showMessage("실험 종료. 역시 이번 실험체는 꽤 빠르군. \n기억을 몇 번만 더 리셋해보지. 확실한 결과가 필요해.");

		}


		return true;
		});
	scene2_door->setOnKeypadCallback([&](ObjectPtr object)->bool {
		scene2_locked = false;
		showMessage("철커덕!");
		scene2_door->setImage("Images/열린-문.png");
		scene2_open = true;

		return true;
		});

	scene2_keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showKeypad("HELPME", scene2_door);
		return true;
		});

	scene2_light_switch->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (scene2_light_check == false) {
			scene2->setLight(0.1f);
			scene2_password->hide();
			scene2_light_check = true;
		}
		else {
			scene2->setLight(1.0f);
			scene2_password->show();
			scene2_light_check = false;

		}
		return true;
		});

	//씬2 끝
	//씬3 시작(에필로그)
	auto  scene3_ecjector = Object::create("Images/주사기.png", scene3, 600, 200);
	scene3_ecjector->setScale(0.3f);
	scene3_ecjector->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		endGame();

		return true;
		});

	startGame(scene1);

	return 0;


}