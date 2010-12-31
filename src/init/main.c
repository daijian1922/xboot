/*
 * init/main.c
 *
 * Copyright (c) 2007-2008  jianjun jiang <jerryjianjun@gmail.com>
 * official site: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs.h>
#include <default.h>
#include <xboot.h>
#include <init.h>
#include <mode/mode.h>
#include <time/xtime.h>
#include <xboot/log.h>
#include <xboot/machine.h>
#include <xboot/panic.h>

/*
 * the entry of main function.
 */
int xboot_main(int argc, char *argv[])
{
	/* do all init calls */
	do_initcalls();

	/* do system xtime */
	do_system_xtime();

	/* mount root filesystem */
	do_system_rootfs();

	/* load system configure */
	do_system_cfg();

	/* load system fonts */
	do_system_fonts();

	/* do system anti-piracy */
	do_system_antipiracy();

	/* wait a moment */
	do_system_wait();

	/* run loop */
	while(1)
	{
		/*
		 * normal mode
		 */
		if(xboot_get_mode() == MODE_NORMAL)
		{
			run_normal_mode();
		}

		/*
		 * shell mode
		 */
		else if(xboot_get_mode() == MODE_SHELL)
		{
			run_shell_mode();
		}

		/*
		 * memu mode
		 */
		else if(xboot_get_mode() == MODE_MENU)
		{
			run_menu_mode();
		}

		/*
		 * graphic mode
		 */
		else if(xboot_get_mode() == MODE_GRAPHIC)
		{
			run_graphic_mode();
		}

		/*
		 * not support other mode and system panic.
		 */
		else
		{
			/*
			 * system panic.
			 */
			panic("do not support the mode(%ld), system panic", xboot_get_mode());
		}
	}

	/* do all exit calls */
	do_exitcalls();

	/* xboot return */
	return 0;
}
