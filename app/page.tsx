"use client";

import Main from "../components/main";
import { CppProvider } from "@/utils/hooks/useCpp";

export default function Home() {

  return (<CppProvider>
    <Main/>
  </CppProvider>);
}
