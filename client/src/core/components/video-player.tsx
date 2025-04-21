import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";

export interface VideoPlayerProps {
  src?: string;
}

export default function VideoPlayer({ src }: VideoPlayerProps) {
  const { i18n } = useTranslation();
  const [subtitleSrc, setSubtitleSrc] = useState<string | undefined>(undefined);

  useEffect(() => {
    if (src) {
      setSubtitleSrc(`${src.slice(0, -6)}subtitles/${i18n.language}`);
    }
  }, [src, i18n.language]);

  useEffect(() => {
    return () => {
      src = '';
    };
  }, [src]);

  return (
    <>
      <video key={src} controls style={{ maxHeight: '50dvh' }}>
        <source src={src} type="video/mp4" />
        <track
            key={"en"}
            default={i18n.language == "en"}
            kind="subtitles"
            label={"en"}
            srcLang={"en"}
            src={`${src?.slice(0, -6)}subtitles/en`}
          />
        {subtitleSrc && i18n.language != "en" && (
          <track
            key={i18n.language}
            default={true}
            kind="subtitles"
            label={i18n.language}
            srcLang={i18n.language}
            src={subtitleSrc}
          />
        )}
      </video>
    </>
  );
}
