/* DLL configurator control head by Iconoclast
 *
 * Macro controls over RSP virtualization behaviors are all switched here.
 * There is no GUI to config such as zilmar's `DllConfig` export because
 * obviously such run-time checks slow down the emulation by checking the
 * configurations per billions of opcode iterations.  Anyone can add a WINGUI
 * config if they like, but I doubt that the performance impact is worth it.
 */

#define _CRT_SECURE_NO_WARNINGS
/* This is only here for people using modern Microsoft compilers.
 * Usually the default warning level complains over "deprecated" CRT methods.
 * It's basically Microsoft's way of saying they're better than everyone.
 */

// #undef  MINIMUM_MESSAGE_PRIORITY
/* Many people will have different uses for an RSP emulator.
 * Some people only want to see message boxes for definite RSP LLE errors.
 * Other people are interested in being notified of technical RSP oddities.
 * I have standardized the following priority levels for message boxes:
 *     0:  Any and all message interrupts in this code will notify the user.
 *     1:  Interrupt SP emulation with messages of at least curious cases.
 *     2:  Draw message boxes for N64 situations *probably* unemulated.
 *     3:  Only notify the user of absolute problems in the emulator.
 *     4:  Disable all message printing (less CRT/USER32 lib dependency)
 *         (and also less interference with leisure of full-screen game play)
 * This macro is mainly for maintainability as well as cross-OS portability
 * by calling a custom method which uses the API-specific message print call.
 * See the `void message()` for details on this centralized API invocation.
 */

// #undef  EXTERN_COMMAND_LIST_GBI
/* If this is defined, the RSP never executes graphics tasks.
 * Those will all be sent to the video plugin for simulation processing.
 */
// #undef  EXTERN_COMMAND_LIST_ABI
/* If this is defined, the RSP never executes audio tasks; use audio plugin.
 * Enabling both of these does not guarantee that the RSP will never execute.
 */

// #undef  SEMAPHORE_LOCK_CORRECTIONS
/* The CPU-RSP semaphore is a lock defining synchronization with the host.
 * As of the time in which bpoint reversed the RSP, host interpretation of
 * this lock was incorrect.  The problem has been inherent for a very long
 * time until a rather recent update applied between Project64 1.7:2.0.
 *
 * If this is on, 1964 and Mupen64 will have no sound for [any?] games.
 * It will be almost completely useless on Project64 1.6 or older.
 * The exception is HLE audio, where it will work for almost every game.
 *
 * Keep this off when using audio LLE or playing games booting off the NUS-
 * CIC-6105 chip (also uses the semaphore); keep it on with Project64 2.0.
 */

// #undef  WAIT_FOR_CPU_HOST
/*
 * Bad cycle timing on the part of the CPU host generally means that some
 * SP tasks could be started and end up operating on non-up-to-date SP
 * status register signal bits (SIG0:SIG7).  Enable this setting to restart
 * the RSP task after exceeding 10 counts of reading the SP status register
 * from within the current task.
 * This will work ONLY with Project64 2.0 at the moment (or some of 1.7.x).
 */

// #undef  SP_EXECUTE_LOG
/* This is my mechanism to use file output of 32 bits per each SP operation.
 * I use this in conjunction with my EXE to handle debug, but still checking
 * every single frame even with file output turned off is ~1-2 VI/s slower.
 */

// #undef  VU_EMULATE_SCALAR_ACCUMULATOR_READ
/* VSAW is the only RSP instruction that can access the vector accumulator
 * elements directly.  In the original RSP for Ultra64 this was supposed to
 * be called `VSAR` "Vector Accumulator Read (and Write)".  (The 'S' probably
 * means "Scalar", if not "Select" or "Store".)  Current RSP emulators agree
 * that in VSAW, the accumulator is copied over to VR[vd], but there is a new
 * step no emulator supports.  In the original VSAR, that behavior is before
 * VR[vs] is copied to those accumulator elements.  By the time this opcode
 * got renamed to "VSAW", however, the acknowledgement of this ceased to be.
 */

/* Choose whether to define, or keep undefined, the above macros. */
#define MINIMUM_MESSAGE_PRIORITY    1 // show most messages of RSP weirdness
#define EXTERN_COMMAND_LIST_GBI
#define EXTERN_COMMAND_LIST_ABI
#define SEMAPHORE_LOCK_CORRECTIONS
#define WAIT_FOR_CPU_HOST
// #define SP_EXECUTE_LOG // For debugging only.  Keep it off to free CPU.
// #define VU_EMULATE_SCALAR_ACCUMULATOR_READ // experimental but needs tests

static unsigned char conf[32];
char filename[16] = "rsp_conf.bin";
/*
 * The name of the config file is subject to change.
 * On InitiateRSP, plugin checks if a file named after the game code in the
 * ROM header of the loaded ROM exists.  If so, load the settings per-ROM.
 */

#define L_TITLE "Iconoclast's RSP Interpreter"
#define L_ABOUT "Thanks for test RDP:  Jabo, ziggy, angrylion\n"\
                "SP thread examples:  bpoint, zilmar, Ville Linde"

#define L_NAME "Simple SP Interpreter"
