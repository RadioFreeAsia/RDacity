# Makefile for PO directory in any package using GNU gettext.
# Copyright (C) 1995-1997, 2000-2007, 2009-2010 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU General Public
# License but which still want to provide support for the GNU gettext
# functionality.
# Please note that the actual code of GNU gettext is covered by the GNU
# General Public License and is *not* in the public domain.
#
# Origin: gettext-0.18
GETTEXT_MACRO_VERSION = 0.18

PACKAGE = audacity
VERSION = 2.0.6
PACKAGE_BUGREPORT = 

SHELL = /bin/sh


srcdir = .
top_srcdir = ..


prefix = /usr/local/
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
datadir = ${datarootdir}
localedir = ${datarootdir}/locale
gettextsrcdir = $(datadir)/gettext/po

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

# We use $(mkdir_p).
# In automake <= 1.9.x, $(mkdir_p) is defined either as "mkdir -p --" or as
# "$(mkinstalldirs)" or as "$(install_sh) -d". For these automake versions,
# ${SHELL} /home/bakert/RDacity-2/RDacity/autotools/install-sh does not start with $(SHELL), so we add it.
# In automake >= 1.10, /usr/bin/mkdir -p is derived from ${MKDIR_P}, which is defined
# either as "/path/to/mkdir -p" or ".../install-sh -c -d". For these automake
# versions, $(mkinstalldirs) and $(install_sh) are unused.
mkinstalldirs = $(SHELL) ${SHELL} /home/bakert/RDacity-2/RDacity/autotools/install-sh -d
install_sh = $(SHELL) ${SHELL} /home/bakert/RDacity-2/RDacity/autotools/install-sh
MKDIR_P = /usr/bin/mkdir -p
mkdir_p = /usr/bin/mkdir -p

GMSGFMT_ = /usr/bin/msgfmt
GMSGFMT_no = /usr/bin/msgfmt
GMSGFMT_yes = /usr/bin/msgfmt
GMSGFMT = $(GMSGFMT_$(USE_MSGCTXT))
MSGFMT_ = /usr/bin/msgfmt
MSGFMT_no = /usr/bin/msgfmt
MSGFMT_yes = /usr/bin/msgfmt
MSGFMT = $(MSGFMT_$(USE_MSGCTXT))
XGETTEXT_ = /usr/bin/xgettext
XGETTEXT_no = /usr/bin/xgettext
XGETTEXT_yes = /usr/bin/xgettext
XGETTEXT = $(XGETTEXT_$(USE_MSGCTXT))
MSGMERGE = msgmerge
MSGMERGE_UPDATE = /usr/bin/msgmerge --update
MSGINIT = msginit
MSGCONV = msgconv
MSGFILTER = msgfilter

POFILES =  af.po ar.po be.po bg.po bn.po bs.po ca.po ca_ES@valencia.po cs.po cy.po da.po de.po el.po es.po eu.po fa.po fi.po fr.po ga.po gl.po he.po hi.po hr.po hu.po hy.po id.po it.po ja.po ka.po km.po ko.po lt.po mk.po my.po nb.po nl.po oc.po pl.po pt_PT.po pt_BR.po ro.po ru.po sk.po sl.po sr_RS.po sr_RS@latin.po sv.po ta.po tg.po tr.po uk.po vi.po zh_CN.po zh_TW.po
GMOFILES =  af.gmo ar.gmo be.gmo bg.gmo bn.gmo bs.gmo ca.gmo ca_ES@valencia.gmo cs.gmo cy.gmo da.gmo de.gmo el.gmo es.gmo eu.gmo fa.gmo fi.gmo fr.gmo ga.gmo gl.gmo he.gmo hi.gmo hr.gmo hu.gmo hy.gmo id.gmo it.gmo ja.gmo ka.gmo km.gmo ko.gmo lt.gmo mk.gmo my.gmo nb.gmo nl.gmo oc.gmo pl.gmo pt_PT.gmo pt_BR.gmo ro.gmo ru.gmo sk.gmo sl.gmo sr_RS.gmo sr_RS@latin.gmo sv.gmo ta.gmo tg.gmo tr.gmo uk.gmo vi.gmo zh_CN.gmo zh_TW.gmo
UPDATEPOFILES =  af.po-update ar.po-update be.po-update bg.po-update bn.po-update bs.po-update ca.po-update ca_ES@valencia.po-update cs.po-update cy.po-update da.po-update de.po-update el.po-update es.po-update eu.po-update fa.po-update fi.po-update fr.po-update ga.po-update gl.po-update he.po-update hi.po-update hr.po-update hu.po-update hy.po-update id.po-update it.po-update ja.po-update ka.po-update km.po-update ko.po-update lt.po-update mk.po-update my.po-update nb.po-update nl.po-update oc.po-update pl.po-update pt_PT.po-update pt_BR.po-update ro.po-update ru.po-update sk.po-update sl.po-update sr_RS.po-update sr_RS@latin.po-update sv.po-update ta.po-update tg.po-update tr.po-update uk.po-update vi.po-update zh_CN.po-update zh_TW.po-update
DUMMYPOFILES =  af.nop ar.nop be.nop bg.nop bn.nop bs.nop ca.nop ca_ES@valencia.nop cs.nop cy.nop da.nop de.nop el.nop es.nop eu.nop fa.nop fi.nop fr.nop ga.nop gl.nop he.nop hi.nop hr.nop hu.nop hy.nop id.nop it.nop ja.nop ka.nop km.nop ko.nop lt.nop mk.nop my.nop nb.nop nl.nop oc.nop pl.nop pt_PT.nop pt_BR.nop ro.nop ru.nop sk.nop sl.nop sr_RS.nop sr_RS@latin.nop sv.nop ta.nop tg.nop tr.nop uk.nop vi.nop zh_CN.nop zh_TW.nop
DISTFILES.common = Makefile.in.in remove-potcdate.sin \
$(DISTFILES.common.extra1) $(DISTFILES.common.extra2) $(DISTFILES.common.extra3)
DISTFILES = $(DISTFILES.common) Makevars POTFILES.in \
$(POFILES) $(GMOFILES) \
$(DISTFILES.extra1) $(DISTFILES.extra2) $(DISTFILES.extra3)

POTFILES = \
     ../include/audacity/ConfigInterface.h \
     ../include/audacity/EffectAutomationParameters.h \
     ../include/audacity/EffectInterface.h \
     ../include/audacity/IdentInterface.h \
     ../include/audacity/ImporterInterface.h \
     ../include/audacity/ModuleInterface.h \
     ../include/audacity/PluginInterface.h \
     ../include/audacity/Types.h \
     ../lib-src/FileDialog/FileDialog.cpp \
     ../lib-src/FileDialog/FileDialog.h \
     ../lib-src/FileDialog/gtk/FileDialogPrivate.cpp \
     ../lib-src/FileDialog/gtk/FileDialogPrivate.h \
     ../lib-src/FileDialog/mac/FileDialogPrivate.h \
     ../lib-src/FileDialog/mac/FileDialogPrivate.mm \
     ../lib-src/FileDialog/win/FileDialogPrivate.cpp \
     ../lib-src/FileDialog/win/FileDialogPrivate.h \
     ../lib-src/mod-null/ModNullCallback.cpp \
     ../lib-src/mod-null/ModNullCallback.h \
     ../lib-src/mod-nyq-bench/NyqBench.cpp \
     ../lib-src/mod-nyq-bench/NyqBench.h \
     ../lib-src/mod-script-pipe/PipeServer.cpp \
     ../lib-src/mod-script-pipe/ScripterCallback.cpp \
     ../lib-src/mod-script-pipe/ScripterCallback.h \
     ../src/AColor.cpp \
     ../src/AColor.h \
     ../src/AboutDialog.cpp \
     ../src/AboutDialog.h \
     ../src/AllThemeResources.h \
     ../src/Audacity.h \
     ../src/AudacityApp.cpp \
     ../src/AudacityApp.h \
     ../src/AudacityHeaders.cpp \
     ../src/AudacityHeaders.h \
     ../src/AudacityLogger.cpp \
     ../src/AudacityLogger.h \
     ../src/AudioIO.cpp \
     ../src/AudioIO.h \
     ../src/AudioIOListener.h \
     ../src/AutoRecovery.cpp \
     ../src/AutoRecovery.h \
     ../src/BatchCommandDialog.cpp \
     ../src/BatchCommandDialog.h \
     ../src/BatchCommands.cpp \
     ../src/BatchCommands.h \
     ../src/BatchProcessDialog.cpp \
     ../src/BatchProcessDialog.h \
     ../src/Benchmark.cpp \
     ../src/Benchmark.h \
     ../src/BlockFile.cpp \
     ../src/BlockFile.h \
     ../src/CrossFade.cpp \
     ../src/CrossFade.h \
     ../src/Dependencies.cpp \
     ../src/Dependencies.h \
     ../src/DeviceChange.cpp \
     ../src/DeviceChange.h \
     ../src/DeviceManager.cpp \
     ../src/DeviceManager.h \
     ../src/Diags.cpp \
     ../src/Diags.h \
     ../src/DirManager.cpp \
     ../src/DirManager.h \
     ../src/Dither.cpp \
     ../src/Dither.h \
     ../src/Envelope.cpp \
     ../src/Envelope.h \
     ../src/Experimental.h \
     ../src/FFT.cpp \
     ../src/FFT.h \
     ../src/FFmpeg.cpp \
     ../src/FFmpeg.h \
     ../src/FileFormats.cpp \
     ../src/FileFormats.h \
     ../src/FileIO.cpp \
     ../src/FileIO.h \
     ../src/FileNames.cpp \
     ../src/FileNames.h \
     ../src/FreqWindow.cpp \
     ../src/FreqWindow.h \
     ../src/HelpText.cpp \
     ../src/HelpText.h \
     ../src/HistoryWindow.cpp \
     ../src/HistoryWindow.h \
     ../src/ImageManipulation.cpp \
     ../src/ImageManipulation.h \
     ../src/Internat.cpp \
     ../src/Internat.h \
     ../src/InterpolateAudio.cpp \
     ../src/InterpolateAudio.h \
     ../src/LabelDialog.cpp \
     ../src/LabelDialog.h \
     ../src/LabelTrack.cpp \
     ../src/LabelTrack.h \
     ../src/LangChoice.cpp \
     ../src/LangChoice.h \
     ../src/Languages.cpp \
     ../src/Languages.h \
     ../src/Legacy.cpp \
     ../src/Legacy.h \
     ../src/LoadModules.cpp \
     ../src/LoadModules.h \
     ../src/Lyrics.cpp \
     ../src/Lyrics.h \
     ../src/LyricsWindow.cpp \
     ../src/LyricsWindow.h \
     ../src/MacroMagic.h \
     ../src/Matrix.cpp \
     ../src/Matrix.h \
     ../src/Menus.cpp \
     ../src/Menus.h \
     ../src/Mix.cpp \
     ../src/Mix.h \
     ../src/MixerBoard.cpp \
     ../src/MixerBoard.h \
     ../src/ModuleManager.cpp \
     ../src/ModuleManager.h \
     ../src/NoteTrack.cpp \
     ../src/NoteTrack.h \
     ../src/NumberScale.h \
     ../src/PitchName.cpp \
     ../src/PitchName.h \
     ../src/PlatformCompatibility.cpp \
     ../src/PlatformCompatibility.h \
     ../src/PluginManager.cpp \
     ../src/PluginManager.h \
     ../src/Prefs.cpp \
     ../src/Prefs.h \
     ../src/Printing.cpp \
     ../src/Printing.h \
     ../src/Profiler.cpp \
     ../src/Profiler.h \
     ../src/Project.cpp \
     ../src/Project.h \
     ../src/RealFFTf.cpp \
     ../src/RealFFTf.h \
     ../src/RealFFTf48x.cpp \
     ../src/RealFFTf48x.h \
     ../src/Resample.cpp \
     ../src/Resample.h \
     ../src/RevisionIdent.h \
     ../src/RingBuffer.cpp \
     ../src/RingBuffer.h \
     ../src/SampleFormat.cpp \
     ../src/SampleFormat.h \
     ../src/Screenshot.cpp \
     ../src/Screenshot.h \
     ../src/SelectedRegion.cpp \
     ../src/SelectedRegion.h \
     ../src/Sequence.cpp \
     ../src/Sequence.h \
     ../src/Shuttle.cpp \
     ../src/Shuttle.h \
     ../src/ShuttleGui.cpp \
     ../src/ShuttleGui.h \
     ../src/ShuttlePrefs.cpp \
     ../src/ShuttlePrefs.h \
     ../src/Snap.cpp \
     ../src/Snap.h \
     ../src/SoundActivatedRecord.cpp \
     ../src/SoundActivatedRecord.h \
     ../src/Spectrum.cpp \
     ../src/Spectrum.h \
     ../src/SplashDialog.cpp \
     ../src/SplashDialog.h \
     ../src/SseMathFuncs.cpp \
     ../src/SseMathFuncs.h \
     ../src/Tags.cpp \
     ../src/Tags.h \
     ../src/Theme.cpp \
     ../src/Theme.h \
     ../src/ThemeAsCeeCode.h \
     ../src/TimeDialog.cpp \
     ../src/TimeDialog.h \
     ../src/TimeTrack.cpp \
     ../src/TimeTrack.h \
     ../src/TimerRecordDialog.cpp \
     ../src/TimerRecordDialog.h \
     ../src/Track.cpp \
     ../src/Track.h \
     ../src/TrackArtist.cpp \
     ../src/TrackArtist.h \
     ../src/TrackPanel.cpp \
     ../src/TrackPanel.h \
     ../src/TrackPanelAx.cpp \
     ../src/TrackPanelAx.h \
     ../src/TrackPanelListener.h \
     ../src/TranslatableStringArray.h \
     ../src/UndoManager.cpp \
     ../src/UndoManager.h \
     ../src/ViewInfo.cpp \
     ../src/ViewInfo.h \
     ../src/VoiceKey.cpp \
     ../src/VoiceKey.h \
     ../src/WaveClip.cpp \
     ../src/WaveClip.h \
     ../src/WaveTrack.cpp \
     ../src/WaveTrack.h \
     ../src/WaveTrackLocation.h \
     ../src/WrappedType.cpp \
     ../src/WrappedType.h \
     ../src/blockfile/LegacyAliasBlockFile.cpp \
     ../src/blockfile/LegacyAliasBlockFile.h \
     ../src/blockfile/LegacyBlockFile.cpp \
     ../src/blockfile/LegacyBlockFile.h \
     ../src/blockfile/ODDecodeBlockFile.cpp \
     ../src/blockfile/ODDecodeBlockFile.h \
     ../src/blockfile/ODPCMAliasBlockFile.cpp \
     ../src/blockfile/ODPCMAliasBlockFile.h \
     ../src/blockfile/PCMAliasBlockFile.cpp \
     ../src/blockfile/PCMAliasBlockFile.h \
     ../src/blockfile/SilentBlockFile.cpp \
     ../src/blockfile/SilentBlockFile.h \
     ../src/blockfile/SimpleBlockFile.cpp \
     ../src/blockfile/SimpleBlockFile.h \
     ../src/commands/AppCommandEvent.cpp \
     ../src/commands/AppCommandEvent.h \
     ../src/commands/BatchEvalCommand.cpp \
     ../src/commands/BatchEvalCommand.h \
     ../src/commands/Command.cpp \
     ../src/commands/Command.h \
     ../src/commands/CommandBuilder.cpp \
     ../src/commands/CommandBuilder.h \
     ../src/commands/CommandDirectory.cpp \
     ../src/commands/CommandDirectory.h \
     ../src/commands/CommandHandler.cpp \
     ../src/commands/CommandHandler.h \
     ../src/commands/CommandManager.cpp \
     ../src/commands/CommandManager.h \
     ../src/commands/CommandMisc.h \
     ../src/commands/CommandSignature.cpp \
     ../src/commands/CommandSignature.h \
     ../src/commands/CommandTargets.h \
     ../src/commands/CommandType.cpp \
     ../src/commands/CommandType.h \
     ../src/commands/CompareAudioCommand.cpp \
     ../src/commands/CompareAudioCommand.h \
     ../src/commands/ExecMenuCommand.cpp \
     ../src/commands/ExecMenuCommand.h \
     ../src/commands/GetAllMenuCommands.cpp \
     ../src/commands/GetAllMenuCommands.h \
     ../src/commands/GetProjectInfoCommand.cpp \
     ../src/commands/GetProjectInfoCommand.h \
     ../src/commands/GetTrackInfoCommand.cpp \
     ../src/commands/GetTrackInfoCommand.h \
     ../src/commands/HelpCommand.cpp \
     ../src/commands/HelpCommand.h \
     ../src/commands/ImportExportCommands.cpp \
     ../src/commands/ImportExportCommands.h \
     ../src/commands/Keyboard.cpp \
     ../src/commands/Keyboard.h \
     ../src/commands/MessageCommand.cpp \
     ../src/commands/MessageCommand.h \
     ../src/commands/OpenSaveCommands.cpp \
     ../src/commands/OpenSaveCommands.h \
     ../src/commands/PreferenceCommands.cpp \
     ../src/commands/PreferenceCommands.h \
     ../src/commands/ResponseQueue.cpp \
     ../src/commands/ResponseQueue.h \
     ../src/commands/ScreenshotCommand.cpp \
     ../src/commands/ScreenshotCommand.h \
     ../src/commands/ScriptCommandRelay.cpp \
     ../src/commands/ScriptCommandRelay.h \
     ../src/commands/SelectCommand.cpp \
     ../src/commands/SelectCommand.h \
     ../src/commands/SetProjectInfoCommand.cpp \
     ../src/commands/SetProjectInfoCommand.h \
     ../src/commands/SetTrackInfoCommand.cpp \
     ../src/commands/SetTrackInfoCommand.h \
     ../src/commands/Validators.h \
     ../src/configtemplate.h \
     ../src/effects/Amplify.cpp \
     ../src/effects/Amplify.h \
     ../src/effects/AutoDuck.cpp \
     ../src/effects/AutoDuck.h \
     ../src/effects/BassTreble.cpp \
     ../src/effects/BassTreble.h \
     ../src/effects/Biquad.cpp \
     ../src/effects/Biquad.h \
     ../src/effects/ChangePitch.cpp \
     ../src/effects/ChangePitch.h \
     ../src/effects/ChangeSpeed.cpp \
     ../src/effects/ChangeSpeed.h \
     ../src/effects/ChangeTempo.cpp \
     ../src/effects/ChangeTempo.h \
     ../src/effects/ClickRemoval.cpp \
     ../src/effects/ClickRemoval.h \
     ../src/effects/Compressor.cpp \
     ../src/effects/Compressor.h \
     ../src/effects/Contrast.cpp \
     ../src/effects/Contrast.h \
     ../src/effects/DtmfGen.cpp \
     ../src/effects/DtmfGen.h \
     ../src/effects/Echo.cpp \
     ../src/effects/Echo.h \
     ../src/effects/Effect.cpp \
     ../src/effects/Effect.h \
     ../src/effects/EffectManager.cpp \
     ../src/effects/EffectManager.h \
     ../src/effects/EffectRack.cpp \
     ../src/effects/EffectRack.h \
     ../src/effects/Equalization.cpp \
     ../src/effects/Equalization.h \
     ../src/effects/Equalization48x.cpp \
     ../src/effects/Equalization48x.h \
     ../src/effects/Fade.cpp \
     ../src/effects/Fade.h \
     ../src/effects/FindClipping.cpp \
     ../src/effects/FindClipping.h \
     ../src/effects/Generator.cpp \
     ../src/effects/Generator.h \
     ../src/effects/Invert.cpp \
     ../src/effects/Invert.h \
     ../src/effects/Leveller.cpp \
     ../src/effects/Leveller.h \
     ../src/effects/LoadEffects.cpp \
     ../src/effects/LoadEffects.h \
     ../src/effects/Noise.cpp \
     ../src/effects/Noise.h \
     ../src/effects/NoiseReduction.cpp \
     ../src/effects/NoiseReduction.h \
     ../src/effects/NoiseRemoval.cpp \
     ../src/effects/NoiseRemoval.h \
     ../src/effects/Normalize.cpp \
     ../src/effects/Normalize.h \
     ../src/effects/Paulstretch.cpp \
     ../src/effects/Paulstretch.h \
     ../src/effects/Phaser.cpp \
     ../src/effects/Phaser.h \
     ../src/effects/Repair.cpp \
     ../src/effects/Repair.h \
     ../src/effects/Repeat.cpp \
     ../src/effects/Repeat.h \
     ../src/effects/Reverb.cpp \
     ../src/effects/Reverb.h \
     ../src/effects/Reverb_libSoX.h \
     ../src/effects/Reverse.cpp \
     ../src/effects/Reverse.h \
     ../src/effects/SBSMSEffect.cpp \
     ../src/effects/SBSMSEffect.h \
     ../src/effects/ScienFilter.cpp \
     ../src/effects/ScienFilter.h \
     ../src/effects/ScoreAlignDialog.cpp \
     ../src/effects/ScoreAlignDialog.h \
     ../src/effects/Silence.cpp \
     ../src/effects/Silence.h \
     ../src/effects/SimpleMono.cpp \
     ../src/effects/SimpleMono.h \
     ../src/effects/SoundTouchEffect.cpp \
     ../src/effects/SoundTouchEffect.h \
     ../src/effects/StereoToMono.cpp \
     ../src/effects/StereoToMono.h \
     ../src/effects/TimeScale.cpp \
     ../src/effects/TimeScale.h \
     ../src/effects/TimeWarper.cpp \
     ../src/effects/TimeWarper.h \
     ../src/effects/ToneGen.cpp \
     ../src/effects/ToneGen.h \
     ../src/effects/TruncSilence.cpp \
     ../src/effects/TruncSilence.h \
     ../src/effects/TwoPassSimpleMono.cpp \
     ../src/effects/TwoPassSimpleMono.h \
     ../src/effects/VST/VSTControl.h \
     ../src/effects/VST/VSTControlGTK.cpp \
     ../src/effects/VST/VSTControlGTK.h \
     ../src/effects/VST/VSTControlMSW.cpp \
     ../src/effects/VST/VSTControlMSW.h \
     ../src/effects/VST/VSTControlOSX.h \
     ../src/effects/VST/VSTControlOSX.mm \
     ../src/effects/VST/VSTEffect.cpp \
     ../src/effects/VST/VSTEffect.h \
     ../src/effects/VST/aeffectx.h \
     ../src/effects/Wahwah.cpp \
     ../src/effects/Wahwah.h \
     ../src/effects/audiounits/AUControl.h \
     ../src/effects/audiounits/AUControl.mm \
     ../src/effects/audiounits/AudioUnitEffect.cpp \
     ../src/effects/audiounits/AudioUnitEffect.h \
     ../src/effects/ladspa/LadspaEffect.cpp \
     ../src/effects/ladspa/LadspaEffect.h \
     ../src/effects/ladspa/ladspa.h \
     ../src/effects/lv2/LV2Effect.cpp \
     ../src/effects/lv2/LV2Effect.h \
     ../src/effects/lv2/LoadLV2.cpp \
     ../src/effects/lv2/LoadLV2.h \
     ../src/effects/lv2/win_gtk.h \
     ../src/effects/nyquist/LoadNyquist.cpp \
     ../src/effects/nyquist/LoadNyquist.h \
     ../src/effects/nyquist/Nyquist.cpp \
     ../src/effects/nyquist/Nyquist.h \
     ../src/effects/vamp/LoadVamp.cpp \
     ../src/effects/vamp/LoadVamp.h \
     ../src/effects/vamp/VampEffect.cpp \
     ../src/effects/vamp/VampEffect.h \
     ../src/export/Export.cpp \
     ../src/export/Export.h \
     ../src/export/ExportCL.cpp \
     ../src/export/ExportCL.h \
     ../src/export/ExportFFmpeg.cpp \
     ../src/export/ExportFFmpeg.h \
     ../src/export/ExportFFmpegDialogs.cpp \
     ../src/export/ExportFFmpegDialogs.h \
     ../src/export/ExportFLAC.cpp \
     ../src/export/ExportFLAC.h \
     ../src/export/ExportMP2.cpp \
     ../src/export/ExportMP2.h \
     ../src/export/ExportMP3.cpp \
     ../src/export/ExportMP3.h \
     ../src/export/ExportMultiple.cpp \
     ../src/export/ExportMultiple.h \
     ../src/export/ExportOGG.cpp \
     ../src/export/ExportOGG.h \
     ../src/export/ExportPCM.cpp \
     ../src/export/ExportPCM.h \
     ../src/float_cast.h \
     ../src/import/FormatClassifier.cpp \
     ../src/import/FormatClassifier.h \
     ../src/import/Import.cpp \
     ../src/import/Import.h \
     ../src/import/ImportFFmpeg.cpp \
     ../src/import/ImportFFmpeg.h \
     ../src/import/ImportFLAC.cpp \
     ../src/import/ImportFLAC.h \
     ../src/import/ImportGStreamer.cpp \
     ../src/import/ImportGStreamer.h \
     ../src/import/ImportLOF.cpp \
     ../src/import/ImportLOF.h \
     ../src/import/ImportMIDI.cpp \
     ../src/import/ImportMIDI.h \
     ../src/import/ImportMP3.cpp \
     ../src/import/ImportMP3.h \
     ../src/import/ImportOGG.cpp \
     ../src/import/ImportOGG.h \
     ../src/import/ImportPCM.cpp \
     ../src/import/ImportPCM.h \
     ../src/import/ImportPlugin.h \
     ../src/import/ImportQT.cpp \
     ../src/import/ImportQT.h \
     ../src/import/ImportRaw.cpp \
     ../src/import/ImportRaw.h \
     ../src/import/MultiFormatReader.cpp \
     ../src/import/MultiFormatReader.h \
     ../src/import/RawAudioGuess.cpp \
     ../src/import/RawAudioGuess.h \
     ../src/import/SpecPowerMeter.cpp \
     ../src/import/SpecPowerMeter.h \
     ../src/ondemand/ODComputeSummaryTask.cpp \
     ../src/ondemand/ODComputeSummaryTask.h \
     ../src/ondemand/ODDecodeFFmpegTask.cpp \
     ../src/ondemand/ODDecodeFFmpegTask.h \
     ../src/ondemand/ODDecodeFlacTask.cpp \
     ../src/ondemand/ODDecodeFlacTask.h \
     ../src/ondemand/ODDecodeTask.cpp \
     ../src/ondemand/ODDecodeTask.h \
     ../src/ondemand/ODManager.cpp \
     ../src/ondemand/ODManager.h \
     ../src/ondemand/ODTask.cpp \
     ../src/ondemand/ODTask.h \
     ../src/ondemand/ODTaskThread.cpp \
     ../src/ondemand/ODTaskThread.h \
     ../src/ondemand/ODWaveTrackTaskQueue.cpp \
     ../src/ondemand/ODWaveTrackTaskQueue.h \
     ../src/prefs/BatchPrefs.cpp \
     ../src/prefs/BatchPrefs.h \
     ../src/prefs/DevicePrefs.cpp \
     ../src/prefs/DevicePrefs.h \
     ../src/prefs/DirectoriesPrefs.cpp \
     ../src/prefs/DirectoriesPrefs.h \
     ../src/prefs/EffectsPrefs.cpp \
     ../src/prefs/EffectsPrefs.h \
     ../src/prefs/ExtImportPrefs.cpp \
     ../src/prefs/ExtImportPrefs.h \
     ../src/prefs/GUIPrefs.cpp \
     ../src/prefs/GUIPrefs.h \
     ../src/prefs/GUISettings.h \
     ../src/prefs/ImportExportPrefs.cpp \
     ../src/prefs/ImportExportPrefs.h \
     ../src/prefs/KeyConfigPrefs.cpp \
     ../src/prefs/KeyConfigPrefs.h \
     ../src/prefs/LibraryPrefs.cpp \
     ../src/prefs/LibraryPrefs.h \
     ../src/prefs/MidiIOPrefs.cpp \
     ../src/prefs/MidiIOPrefs.h \
     ../src/prefs/ModulePrefs.cpp \
     ../src/prefs/ModulePrefs.h \
     ../src/prefs/MousePrefs.cpp \
     ../src/prefs/MousePrefs.h \
     ../src/prefs/PlaybackPrefs.cpp \
     ../src/prefs/PlaybackPrefs.h \
     ../src/prefs/PrefsDialog.cpp \
     ../src/prefs/PrefsDialog.h \
     ../src/prefs/PrefsPanel.h \
     ../src/prefs/ProjectsPrefs.cpp \
     ../src/prefs/ProjectsPrefs.h \
     ../src/prefs/QualityPrefs.cpp \
     ../src/prefs/QualityPrefs.h \
     ../src/prefs/RecordingPrefs.cpp \
     ../src/prefs/RecordingPrefs.h \
     ../src/prefs/SpectrogramSettings.cpp \
     ../src/prefs/SpectrogramSettings.h \
     ../src/prefs/SpectrumPrefs.cpp \
     ../src/prefs/SpectrumPrefs.h \
     ../src/prefs/ThemePrefs.cpp \
     ../src/prefs/ThemePrefs.h \
     ../src/prefs/TracksPrefs.cpp \
     ../src/prefs/TracksPrefs.h \
     ../src/prefs/WarningsPrefs.cpp \
     ../src/prefs/WarningsPrefs.h \
     ../src/prefs/WaveformPrefs.cpp \
     ../src/prefs/WaveformPrefs.h \
     ../src/prefs/WaveformSettings.cpp \
     ../src/prefs/WaveformSettings.h \
     ../src/toolbars/ControlToolBar.cpp \
     ../src/toolbars/ControlToolBar.h \
     ../src/toolbars/DeviceToolBar.cpp \
     ../src/toolbars/DeviceToolBar.h \
     ../src/toolbars/EditToolBar.cpp \
     ../src/toolbars/EditToolBar.h \
     ../src/toolbars/MeterToolBar.cpp \
     ../src/toolbars/MeterToolBar.h \
     ../src/toolbars/MixerToolBar.cpp \
     ../src/toolbars/MixerToolBar.h \
     ../src/toolbars/SelectionBar.cpp \
     ../src/toolbars/SelectionBar.h \
     ../src/toolbars/SelectionBarListener.h \
     ../src/toolbars/SpectralSelectionBar.cpp \
     ../src/toolbars/SpectralSelectionBar.h \
     ../src/toolbars/SpectralSelectionBarListener.h \
     ../src/toolbars/ToolBar.cpp \
     ../src/toolbars/ToolBar.h \
     ../src/toolbars/ToolDock.cpp \
     ../src/toolbars/ToolDock.h \
     ../src/toolbars/ToolManager.cpp \
     ../src/toolbars/ToolManager.h \
     ../src/toolbars/ToolsToolBar.cpp \
     ../src/toolbars/ToolsToolBar.h \
     ../src/toolbars/TranscriptionToolBar.cpp \
     ../src/toolbars/TranscriptionToolBar.h \
     ../src/widgets/AButton.cpp \
     ../src/widgets/AButton.h \
     ../src/widgets/ASlider.cpp \
     ../src/widgets/ASlider.h \
     ../src/widgets/AttachableScrollBar.cpp \
     ../src/widgets/AttachableScrollBar.h \
     ../src/widgets/ErrorDialog.cpp \
     ../src/widgets/ErrorDialog.h \
     ../src/widgets/ExpandingToolBar.cpp \
     ../src/widgets/ExpandingToolBar.h \
     ../src/widgets/FileHistory.cpp \
     ../src/widgets/FileHistory.h \
     ../src/widgets/Grabber.cpp \
     ../src/widgets/Grabber.h \
     ../src/widgets/Grid.cpp \
     ../src/widgets/Grid.h \
     ../src/widgets/HelpSystem.cpp \
     ../src/widgets/HelpSystem.h \
     ../src/widgets/HtmlWindow.cpp \
     ../src/widgets/HtmlWindow.h \
     ../src/widgets/ImageRoll.cpp \
     ../src/widgets/ImageRoll.h \
     ../src/widgets/KeyView.cpp \
     ../src/widgets/KeyView.h \
     ../src/widgets/LinkingHtmlWindow.cpp \
     ../src/widgets/LinkingHtmlWindow.h \
     ../src/widgets/Meter.cpp \
     ../src/widgets/Meter.h \
     ../src/widgets/MultiDialog.cpp \
     ../src/widgets/MultiDialog.h \
     ../src/widgets/NumericTextCtrl.cpp \
     ../src/widgets/NumericTextCtrl.h \
     ../src/widgets/ProgressDialog.cpp \
     ../src/widgets/ProgressDialog.h \
     ../src/widgets/Ruler.cpp \
     ../src/widgets/Ruler.h \
     ../src/widgets/Warning.cpp \
     ../src/widgets/Warning.h \
     ../src/widgets/numformatter.cpp \
     ../src/widgets/numformatter.h \
     ../src/widgets/valnum.cpp \
     ../src/widgets/valnum.h \
     ../src/xml/XMLFileReader.cpp \
     ../src/xml/XMLFileReader.h \
     ../src/xml/XMLTagHandler.cpp \
     ../src/xml/XMLTagHandler.h \
     ../src/xml/XMLWriter.cpp \
     ../src/xml/XMLWriter.h

CATALOGS =  af.gmo ar.gmo be.gmo bg.gmo bn.gmo bs.gmo ca.gmo ca_ES@valencia.gmo cs.gmo cy.gmo da.gmo de.gmo el.gmo es.gmo eu.gmo fa.gmo fi.gmo fr.gmo ga.gmo gl.gmo he.gmo hi.gmo hr.gmo hu.gmo hy.gmo id.gmo it.gmo ja.gmo ka.gmo km.gmo ko.gmo lt.gmo mk.gmo my.gmo nb.gmo nl.gmo oc.gmo pl.gmo pt_PT.gmo pt_BR.gmo ro.gmo ru.gmo sk.gmo sl.gmo sr_RS.gmo sr_RS@latin.gmo sv.gmo ta.gmo tg.gmo tr.gmo uk.gmo vi.gmo zh_CN.gmo zh_TW.gmo

# Makevars gets inserted here. (Don't remove this line!)
# Makefile variables for PO directory in any package using GNU gettext.

# Usually the message domain is the same as the package name.
DOMAIN = $(PACKAGE)

# These two variables depend on the location of this directory.
subdir = po
top_builddir = ..

# These options get passed to xgettext.
XGETTEXT_OPTIONS = --keyword=_ --keyword=N_ --keyword=XO --add-comments=" i18n"

# This is the copyright holder that gets inserted into the header of the
# $(DOMAIN).pot file.  Set this to the copyright holder of the surrounding
# package.  (Note that the msgstr strings, extracted from the package's
# sources, belong to the copyright holder of the package.)  Translators are
# expected to transfer the copyright for their translations to this person
# or entity, or to disclaim their copyright.  The empty string stands for
# the public domain; in this case the translators are expected to disclaim
# their copyright.
COPYRIGHT_HOLDER = Audacity Team

# This is the email address or URL to which the translators shall report
# bugs in the untranslated strings:
# - Strings which are not entire sentences, see the maintainer guidelines
#   in the GNU gettext documentation, section 'Preparing Strings'.
# - Strings which use unclear terms or require additional context to be
#   understood.
# - Strings which make invalid assumptions about notation of date, time or
#   money.
# - Pluralisation problems.
# - Incorrect English spelling.
# - Incorrect formatting.
# It can be your email address, or a mailing list address where translators
# can write to without being subscribed, or the URL of a web page through
# which the translators can contact you.
MSGID_BUGS_ADDRESS = audacity-translation@lists.sourceforge.net

# This is the list of locale categories, beyond LC_MESSAGES, for which the
# message catalogs shall be used.  It is usually empty.
EXTRA_LOCALE_CATEGORIES =

.SUFFIXES:
.SUFFIXES: .po .gmo .mo .sed .sin .nop .po-create .po-update

.po.mo:
	@echo "$(MSGFMT) -c -o $@ $<"; \
	$(MSGFMT) -c -o t-$@ $< && mv t-$@ $@

.po.gmo:
	@lang=`echo $* | sed -e 's,.*/,,'`; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o $${lang}.gmo $${lang}.po"; \
	cd $(srcdir) && rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o t-$${lang}.gmo $${lang}.po && mv t-$${lang}.gmo $${lang}.gmo

.sin.sed:
	sed -e '/^#/d' $< > t-$@
	mv t-$@ $@


all: check-macro-version all-yes

all-yes: stamp-po
all-no:

# Ensure that the gettext macros and this Makefile.in.in are in sync.
check-macro-version:
	@test "$(GETTEXT_MACRO_VERSION)" = "0.18" \
	  || { echo "*** error: gettext infrastructure mismatch: using a Makefile.in.in from gettext version $(GETTEXT_MACRO_VERSION) but the autoconf macros are from gettext version 0.18" 1>&2; \
	       exit 1; \
	     }

# $(srcdir)/$(DOMAIN).pot is only created when needed. When xgettext finds no
# internationalized messages, no $(srcdir)/$(DOMAIN).pot is created (because
# we don't want to bother translators with empty POT files). We assume that
# LINGUAS is empty in this case, i.e. $(POFILES) and $(GMOFILES) are empty.
# In this case, stamp-po is a nop (i.e. a phony target).

# stamp-po is a timestamp denoting the last time at which the CATALOGS have
# been loosely updated. Its purpose is that when a developer or translator
# checks out the package via CVS, and the $(DOMAIN).pot file is not in CVS,
# "make" will update the $(DOMAIN).pot and the $(CATALOGS), but subsequent
# invocations of "make" will do nothing. This timestamp would not be necessary
# if updating the $(CATALOGS) would always touch them; however, the rule for
# $(POFILES) has been designed to not touch files that don't need to be
# changed.
stamp-po: $(srcdir)/$(DOMAIN).pot
	test ! -f $(srcdir)/$(DOMAIN).pot || \
	  test -z "$(GMOFILES)" || $(MAKE) $(GMOFILES)
	@test ! -f $(srcdir)/$(DOMAIN).pot || { \
	  echo "touch stamp-po" && \
	  echo timestamp > stamp-poT && \
	  mv stamp-poT stamp-po; \
	}

# Note: Target 'all' must not depend on target '$(DOMAIN).pot-update',
# otherwise packages like GCC can not be built if only parts of the source
# have been downloaded.

# This target rebuilds $(DOMAIN).pot; it is an expensive operation.
# Note that $(DOMAIN).pot is not touched if it doesn't need to be changed.
$(DOMAIN).pot-update: $(POTFILES) $(srcdir)/POTFILES.in remove-potcdate.sed
	if LC_ALL=C grep 'GNU audacity' $(top_srcdir)/* 2>/dev/null | grep -v 'libtool:' >/dev/null; then \
	  package_gnu='GNU '; \
	else \
	  package_gnu=''; \
	fi; \
	if test -n '$(MSGID_BUGS_ADDRESS)' || test '$(PACKAGE_BUGREPORT)' = '@'PACKAGE_BUGREPORT'@'; then \
	  msgid_bugs_address='$(MSGID_BUGS_ADDRESS)'; \
	else \
	  msgid_bugs_address='$(PACKAGE_BUGREPORT)'; \
	fi; \
	case `$(XGETTEXT) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	  '' | 0.[0-9] | 0.[0-9].* | 0.1[0-5] | 0.1[0-5].* | 0.16 | 0.16.[0-1]*) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	  *) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --package-name="$${package_gnu}audacity" \
	      --package-version='2.0.6' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	esac
	test ! -f $(DOMAIN).po || { \
	  if test -f $(srcdir)/$(DOMAIN).pot; then \
	    sed -f remove-potcdate.sed < $(srcdir)/$(DOMAIN).pot > $(DOMAIN).1po && \
	    sed -f remove-potcdate.sed < $(DOMAIN).po > $(DOMAIN).2po && \
	    if cmp $(DOMAIN).1po $(DOMAIN).2po >/dev/null 2>&1; then \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(DOMAIN).po; \
	    else \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(srcdir)/$(DOMAIN).pot && \
	      mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	    fi; \
	  else \
	    mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	  fi; \
	}

# This rule has no dependencies: we don't need to update $(DOMAIN).pot at
# every "make" invocation, only create it when it is missing.
# Only "make $(DOMAIN).pot-update" or "make dist" will force an update.
$(srcdir)/$(DOMAIN).pot:
	$(MAKE) $(DOMAIN).pot-update

# This target rebuilds a PO file if $(DOMAIN).pot has changed.
# Note that a PO file is not touched if it doesn't need to be changed.
$(POFILES): $(srcdir)/$(DOMAIN).pot
	@lang=`echo $@ | sed -e 's,.*/,,' -e 's/\.po$$//'`; \
	if test -f "$(srcdir)/$${lang}.po"; then \
	  test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	  echo "$${cdcmd}$(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot"; \
	  cd $(srcdir) \
	    && { case `$(MSGMERGE_UPDATE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	           '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) $${lang}.po $(DOMAIN).pot;; \
	           *) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot;; \
	         esac; \
	       }; \
	else \
	  $(MAKE) $${lang}.po-create; \
	fi


install: install-exec install-data
install-exec:
install-data: install-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    $(INSTALL_DATA) $(srcdir)/$$file \
			    $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	  for file in Makevars; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
install-data-no: all
install-data-yes: all
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  if test -r $$cat; then realcat=$$cat; else realcat=$(srcdir)/$$cat; fi; \
	  $(INSTALL_DATA) $$realcat $(DESTDIR)$$dir/$(DOMAIN).mo; \
	  echo "installing $$realcat as $(DESTDIR)$$dir/$(DOMAIN).mo"; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	      rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      ln -s ../LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      ln $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      cp -p $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      echo "installing $$realcat link as $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo"; \
	    fi; \
	  done; \
	done

install-strip: install

installdirs: installdirs-exec installdirs-data
installdirs-exec:
installdirs-data: installdirs-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	else \
	  : ; \
	fi
installdirs-data-no:
installdirs-data-yes:
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	    fi; \
	  done; \
	done

# Define this as empty until I found a useful application.
installcheck:

uninstall: uninstall-exec uninstall-data
uninstall-exec:
uninstall-data: uninstall-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
uninstall-data-no:
uninstall-data-yes:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  for lc in LC_MESSAGES $(EXTRA_LOCALE_CATEGORIES); do \
	    rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	  done; \
	done

check: all

info dvi ps pdf html tags TAGS ctags CTAGS ID:

mostlyclean:
	rm -f remove-potcdate.sed
	rm -f stamp-poT
	rm -f core core.* $(DOMAIN).po $(DOMAIN).1po $(DOMAIN).2po *.new.po
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f stamp-po $(GMOFILES)

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir:
	$(MAKE) update-po
	@$(MAKE) dist2
# This is a separate target because 'update-po' must be executed before.
dist2: stamp-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  dists="$$dists Makevars.template"; \
	fi; \
	if test -f $(srcdir)/$(DOMAIN).pot; then \
	  dists="$$dists $(DOMAIN).pot stamp-po"; \
	fi; \
	if test -f $(srcdir)/ChangeLog; then \
	  dists="$$dists ChangeLog"; \
	fi; \
	for i in 0 1 2 3 4 5 6 7 8 9; do \
	  if test -f $(srcdir)/ChangeLog.$$i; then \
	    dists="$$dists ChangeLog.$$i"; \
	  fi; \
	done; \
	if test -f $(srcdir)/LINGUAS; then dists="$$dists LINGUAS"; fi; \
	for file in $$dists; do \
	  if test -f $$file; then \
	    cp -p $$file $(distdir) || exit 1; \
	  else \
	    cp -p $(srcdir)/$$file $(distdir) || exit 1; \
	  fi; \
	done

update-po: Makefile
	$(MAKE) $(DOMAIN).pot-update
	test -z "$(UPDATEPOFILES)" || $(MAKE) $(UPDATEPOFILES)
	$(MAKE) update-gmo

# General rule for creating PO files.

.nop.po-create:
	@lang=`echo $@ | sed -e 's/\.po-create$$//'`; \
	echo "File $$lang.po does not exist. If you are a translator, you can create it through 'msginit'." 1>&2; \
	exit 1

# General rule for updating PO files.

.nop.po-update:
	@lang=`echo $@ | sed -e 's/\.po-update$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools"; then PATH=`pwd`/../src:$$PATH; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}$(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang $$lang.po $(DOMAIN).pot -o $$lang.new.po"; \
	cd $(srcdir); \
	if { case `$(MSGMERGE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	       '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	       *) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	     esac; \
	   }; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "msgmerge for $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

$(DUMMYPOFILES):

update-gmo: Makefile $(GMOFILES)
	@:

# Recreate Makefile by invoking config.status. Explicitly invoke the shell,
# because execution permission bits may not work on the current file system.
# Use /bin/sh, which is the shell determined by autoconf for the use by its
# scripts, not $(SHELL) which is hardwired to /bin/sh and may be deficient.
Makefile: Makefile.in.in Makevars $(top_builddir)/config.status POTFILES.in LINGUAS
	cd $(top_builddir) \
	  && /bin/sh ./config.status $(subdir)/$@.in po-directories

force:

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
# Special Makefile rules for English message catalogs with quotation marks.

DISTFILES.common.extra1 = quot.sed boldquot.sed en@quot.header en@boldquot.header insert-header.sin Rules-quot

.SUFFIXES: .insert-header .po-update-en

en@quot.po-create:
	$(MAKE) en@quot.po-update
en@boldquot.po-create:
	$(MAKE) en@boldquot.po-update

en@quot.po-update: en@quot.po-update-en
en@boldquot.po-update: en@boldquot.po-update-en

.insert-header.po-update-en:
	@lang=`echo $@ | sed -e 's/\.po-update-en$$//'`; \
	if test "$(PACKAGE)" = "gettext"; then PATH=`pwd`/../src:$$PATH; GETTEXTLIBDIR=`cd $(top_srcdir)/src && pwd`; export GETTEXTLIBDIR; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	ll=`echo $$lang | sed -e 's/@.*//'`; \
	LC_ALL=C; export LC_ALL; \
	cd $(srcdir); \
	if $(MSGINIT) -i $(DOMAIN).pot --no-translator -l $$lang -o - 2>/dev/null | sed -f $$tmpdir/$$lang.insert-header | $(MSGCONV) -t UTF-8 | $(MSGFILTER) sed -f `echo $$lang | sed -e 's/.*@//'`.sed 2>/dev/null > $$tmpdir/$$lang.new.po; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "creation of $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "creation of $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

en@quot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@quot.header/g' $(srcdir)/insert-header.sin > en@quot.insert-header

en@boldquot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@boldquot.header/g' $(srcdir)/insert-header.sin > en@boldquot.insert-header

mostlyclean: mostlyclean-quot
mostlyclean-quot:
	rm -f *.insert-header
