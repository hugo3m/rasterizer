"use client";

import cppDataUrl from '../../lib/cpp.data'; // Webpack will emit this!
import { useState, useEffect, createContext, useContext, ReactNode } from 'react';
import { MainModule } from "@/lib/cpp.js";

const CppContext = createContext<MainModule | undefined>(undefined);

interface CppProviderProps {
  children: ReactNode;
}

const CppProvider = ({ children }: CppProviderProps) => {
  const [module, setModule] = useState<MainModule | undefined>(undefined);

  useEffect(() => {
    const init = async () => {
      // Dynamically load the Emscripten module from the public folder
      const ModuleFactory = await import('../../lib/cpp.js'); // ⬅️ Load directly from /public

      const moduleInstance: MainModule = await ModuleFactory.default({
        locateFile: (path: string) => {
          if (path.endsWith('.data')) {
            return cppDataUrl;
          }
          return path;
        }
      });
      setModule(moduleInstance);
    };
    init();
  }, []);

  return (
    <CppContext.Provider value={module}>
      {children}
    </CppContext.Provider>
  );
};

const useCpp = (): MainModule | undefined => {
  const context = useContext(CppContext);
  return context;
};

export {
  CppProvider,
  useCpp
};