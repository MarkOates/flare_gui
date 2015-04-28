

#include <allegro_flare/allegro_flare.h>
#include <flare_gui/flare_gui.h>

#include <allegro_flare/skeleton.h>

#include <allegro_flare/screens/simple_notification_screen.h>





class BoneFactory
{
public:
	BoneFactory() {}
	static Bone *build_desk_lamp()
	{
		Bone *root = new Bone(vec2d(0, -1), 5);
		Bone *bone = NULL;

		// arm
		bone = root->add_child(vec2d(0.8, 0.5), 15);

		// headlamp
		bone = bone->add_child(vec2d(1, 8), 3);

		root->scale(10);

		return root;
	}
	static Bone *build_angle_test()
	{
		int length = 20;

		Bone *root = new Bone(vec2d(0, -1), length);
		Bone *bone = root;

		for (int i=length; i>=2; i-=2)
		{
			bone = bone->add_child(vec2d(0, 1), i);
		}

		root->scale(5);

		return root;
	}
	static Bone *build_simple_person()
	{
		Bone *root = new Bone(vec2d(0, -1), 0); // the root is the bottom of the neck
												 // top of a spine

		Bone *bone = NULL;
		Bone *pelvis = NULL;


		// head
		bone = root->add_child(vec2d(1, 0), 4); // upper neck
		bone = bone->add_child(vec2d(1, 0), 9); // skull

		// clavicle & right arm
		bone = root->add_child(vec2d(0, 1), 8); // clavicle
		bone = bone->add_child(vec2d(0, 1), 12); // humerus
		bone = bone->add_child(vec2d(1, 0), 12); // radius
		bone->add_child(vec2d(1, 0), 4); // hand

		// clavicle & left arm
		bone = root->add_child(vec2d(0, 1), -8); // clavicle
		bone = bone->add_child(vec2d(0, 1), 12); // humerus
		bone = bone->add_child(vec2d(1, 0), 12); // radius
		bone->add_child(vec2d(1, 0), 4); // hand

		// spine
		pelvis = root->add_child(vec2d(-1, 0), 20); // spine
		
		// pelvis & right leg
		bone = pelvis->add_child(vec2d(0.5, -1), 5, 0); // pelvis
		bone = bone->add_child(vec2d(0.5, 1), 14); 
		bone = bone->add_child(vec2d(1, 0), 12); 
		bone->add_child(vec2d(0, -1), 4); // foot

		// pelvis & left leg
		bone = pelvis->add_child(vec2d(0.5, 1), 5, 0); // pelvis
		bone = bone->add_child(vec2d(1, -2), 14);
		bone = bone->add_child(vec2d(1, 0), 12);
		bone->add_child(vec2d(0, 1), 4); // foot

		root->scale(10);
		return root;
	}
};


/*
talked about makeup
doing each other's hair
make cookies
meeting your man
leggings
bugs so gross
byonce
*/








class SkeletonExampleProgram : public FGUIScreen
{
public:
	FontBin fonts;

	Bone *bone_test;
	int focus_bone_index;
	int rotating;
	SkeletonState skeleton_states[10];
	Motion bone_animator;

	SimpleNotificationScreen *simple_notification_screen;

	SkeletonExampleProgram(Display *disp)
		: FGUIScreen(disp)
		, bone_test(NULL)
		, rotating(0)
		, fonts()
		, focus_bone_index(0)
		, skeleton_states()
		, bone_animator()
		, simple_notification_screen(NULL)
	{
		bone_test = BoneFactory::build_simple_person();
		simple_notification_screen = new SimpleNotificationScreen(display, fonts["DroidSans.ttf 14"]);

		(new FGUIText(this, 10, 17, "Skeleton Example"))->place.align.y = 0.0;

		//ALLEGRO_FONT *button_font = fonts["consola.ttf 19"];
		float button_y = 140;
		(new FGUIButton(this, 100, button_y+60*1, 160, 50, "Frame1"))->attr.set("on_click_send_message", "data/skeleton_ex/frame1.bfs");
		(new FGUIButton(this, 100, button_y+60*2, 160, 50, "Frame2"))->attr.set("on_click_send_message", "data/skeleton_ex/frame2.bfs");
		(new FGUIButton(this, 100, button_y+60*3, 160, 50, "Frame3"))->attr.set("on_click_send_message", "data/skeleton_ex/frame3.bfs");
		(new FGUIButton(this, 100, button_y+60*4, 160, 50, "Frame4"))->attr.set("on_click_send_message", "data/skeleton_ex/frame4.bfs");
		(new FGUIButton(this, 100, button_y+60*5, 160, 50, "Frame5"))->attr.set("on_click_send_message", "data/skeleton_ex/frame5.bfs");
		(new FGUIButton(this, 100, button_y+60*6, 160, 50, "Frame6"))->attr.set("on_click_send_message", "data/skeleton_ex/frame6.bfs");
		(new FGUIButton(this, 100, button_y+60*7, 160, 50, "Frame7"))->attr.set("on_click_send_message", "data/skeleton_ex/frame7.bfs");
		(new FGUIButton(this, 100, button_y+60*8, 160, 50, "Frame8"))->attr.set("on_click_send_message", "data/skeleton_ex/frame8.bfs");
		(new FGUIButton(this, 100, button_y+60*9, 160, 50, "Frame9"))->attr.set("on_click_send_message", "data/skeleton_ex/frame9.bfs");
	}

	void on_message(std::string message) override
	{
		//simple_notification_screen->spawn_notification("message recieved\n\"" + message + "\"");
		SkeletonState state;
		state.load(message);
		move_skeleton_to_state(bone_test, &state, 0.5);
		simple_notification_screen->spawn_notification("file loaded\n\"" + message + "\"");
	}

	void on_timer() override
	{
		bone_animator.update(af::time_now);

		if (rotating)
		{
			float angle = 0.005 * (rotating);
			//bone_test->rotate_deep(angle);
			Bone *focus_bone = bone_test->get_nth_child(focus_bone_index);
			if (focus_bone) focus_bone->rotate_position(angle);
			//else std::cout << "!";
		}
		bone_test->draw(display->width()/2, display->height()/4, focus_bone_index);

		al_draw_text(fonts["DroidSans.ttf 42"], color::white, 10, 17, 0, (tostring("Skeleton Example")).c_str());
		al_draw_text(fonts["consola.ttf 20"], color::white, 10, 60, 0, (tostring("number of bones: ") + tostring(bone_test->get_tree_size())).c_str());
		al_draw_text(fonts["consola.ttf 20"], color::white, 10, 80, 0, (tostring("current focused bone index: ") + tostring(focus_bone_index)).c_str());
		//al_draw_text(fonts["consola.ttf 32"], color::white, 10, 20, 0, tostring(bone_test->get_tree_size()).c_str());

		// draw some nice text at the bottom
		TextObject("press 'L' to load a .bfs file").position(20, display->height()-40).align(0, 1).font(fonts["consola.ttf 20"]).draw();
		TextObject("Use the LEFT or RIGHT to select a bone, then UP or DOWN to rotate").position(20, display->height()-20).align(0, 1).font(fonts["consola.ttf 20"]).draw();
	}

	void move_skeleton_to_state(Bone *bone_root, SkeletonState *state, float speed)
	{
		int bone_tree_size = bone_test->get_tree_size();
		SkeletonState *state_to_move_to = state;
		for (int i=0; i<bone_tree_size; i++)
		{
			Bone *bone = bone_test->get_nth_child(i);
			SkeletonState::BonePositionRecord *bone_position = state_to_move_to->get_frame_by_bone_index(i);
			if (bone && bone_position)
			{
				bone_animator.cmove_to(&bone->position, bone_position->position, 0.3);
				//bone->set_position(frame->position);
			}
			else
			{
				std::cout << "bone error " << bone << " " << bone_position << std::endl;
			}
		}
	}

	void on_key_char() override
	{
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_UP)
		{
			focus_bone_index++;
			if (focus_bone_index > bone_test->get_tree_size()) focus_bone_index = bone_test->get_tree_size();
		}
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			focus_bone_index--;
			if (focus_bone_index < 0) focus_bone_index = 0;
		}
	}

	void on_key_down() override
	{
		//std::cout << af::current_event->keyboard.keycode << std::endl;
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_RIGHT)
		{
			rotating = 1;
		}
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_LEFT)
		{
			rotating = -1;
		}
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_F12)
		{
			std::string screenshot_filename = take_screenshot();
			simple_notification_screen->spawn_notification("screenshot saved\n\"" + screenshot_filename + "\"");
		}
		if (af::current_event->keyboard.keycode >= ALLEGRO_KEY_1 && af::current_event->keyboard.keycode <= ALLEGRO_KEY_9)
		{
			int state_bank_num = af::current_event->keyboard.keycode - ALLEGRO_KEY_1;
			if (af::key_shift)
			{
				//SkeletonState
				skeleton_states[state_bank_num].set(bone_test);
				std::stringstream filename;
				filename << "data/skeleton_states/state" << state_bank_num << ".bfs";
				skeleton_states[state_bank_num].save(filename.str());
				simple_notification_screen->spawn_notification("file saved\n\"" + filename.str() + "\"");
				std::cout << "saved to bank " << state_bank_num << std::endl;
			}
			else
			{
				if (state_bank_num < 0) {}
				else if (state_bank_num >= (int)children.children.size()) {}
				else children.children[state_bank_num]->on_click();
				//set_to_keyframe(bone_test, &frames[frame_bank_num], 0.3);
				//std::cout << "moving to bank " << frame_bank_num << std::endl;
			}
		}
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_L)
		{
			std::string filename = pick_filename();
			if (!filename.empty())
			{
				SkeletonState state;
				state.load(filename);
				move_skeleton_to_state(bone_test, &state, 0.5);
				simple_notification_screen->spawn_notification("file loaded\n\"" + filename + "\"");
			}
		}
	}

	void on_key_up() override
	{
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_RIGHT) rotating = 0;
		if (af::current_event->keyboard.keycode == ALLEGRO_KEY_LEFT) rotating = 0;
	}

	void joy_config_func() override
	{
		simple_notification_screen->spawn_notification("Joystick was added/removed.");
	}
};





int main(int argc, char *argv[])
{
	af::initialize();
	Display *display = af::create_display(1600, 800);
	SkeletonExampleProgram *prog = new SkeletonExampleProgram(display);
	af::run_loop();
}




