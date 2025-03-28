import "./globals.css";

import type { Metadata } from "next";
import localFont from "next/font/local";

const geistSans = localFont({
  src: "./fonts/GeistVF.woff",
  variable: "--font-geist-sans",
  weight: "100 900",
});
const geistMono = localFont({
  src: "./fonts/GeistMonoVF.woff",
  variable: "--font-geist-mono",
  weight: "100 900",
});

export const metadata: Metadata = {
  title: "Rasterizer",
  description: "Rasterizer WASM by hugo3m",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en" className={"flex flex-1 min-h-screen min-w-full"}>
      <body
        className={`${geistSans.variable} ${geistMono.variable} antialiased`} style={{
          display: 'flex',
          flex: 1
        }}
      >
        {children}
      </body>
    </html>
  );
}
