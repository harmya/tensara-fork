import type { ReactNode } from "react";
import Head from "next/head";
import { Box } from "@chakra-ui/react";
import { Header } from "./header";

interface LayoutProps {
  title?: string;
  children: ReactNode;
  ogDescription?: string;
  ogImage?: string;
}

export function Layout({
  title,
  children,
  ogDescription = "A platform for GPU programming challenges. Write efficient CUDA code and compare your solutions with other developers.",
  ogImage = "/tensara_ogimage.png",
}: LayoutProps) {
  return (
    <>
      <Head>
        <title>{title ? `${title} | Tensara` : "Tensara"}</title>
        <meta name="description" content={ogDescription} />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        {ogImage && <meta property="og:image" content={ogImage} />}
      </Head>

      <Box h="100vh" bg="gray.900" display="flex" flexDirection="column">
        <Box px={{ base: 2, md: 4 }} py={{ base: 2, md: 4 }}>
          <Header />
        </Box>

        <Box
          flex="1"
          px={{ base: 2, md: 4 }}
          pb={{ base: 2, md: 4 }}
          overflow="hidden"
        >
          <Box
            bg="brand.secondary"
            borderRadius="xl"
            h="100%"
            p={{ base: 4, md: 6 }}
            overflow="auto"
          >
            {children}
          </Box>
        </Box>
      </Box>
    </>
  );
}
